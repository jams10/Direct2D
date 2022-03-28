#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(const wchar_t* filename, Graphics* gfx)
{
	// 초기화
	this->gfx = gfx;
	bmp = NULL;
	HRESULT hr;

	// WIC 팩토리 생성
	IWICImagingFactory* wicFactory = NULL;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,	// 우리가 만들어 줄 오브젝트의 클래스 아이디.
		NULL,						
		CLSCTX_INPROC_SERVER,       // 오브젝트의 실행 컨텍스트 지정. 동일한 프로세스로 지정함.
		IID_IWICImagingFactory,     // 오브젝트와 상호작용할 인터페이스의 ID
		(LPVOID*)&wicFactory        // 4번째 매개변수로 넘긴 IID에 해당하는 인터페이스가 이곳으로 넘어옴.
	);

	// 디코더 생성
	IWICBitmapDecoder* wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
			filename,                         // 파일 이름
			NULL,							  // 선호 decoder vendor
			GENERIC_READ,					  // 파일 접근을 읽기로 함.
			WICDecodeMetadataCacheOnLoad,     // decoder가 로드될 때 metadata를 캐시.
			&wicDecoder                       // decoder에 대한 포인터.
	);

	// 이미지로 부터 한 프레임을 읽어옴.(gif 파일등은 여러 프레임으로 이루어져 있기 때문에 이런 방식을 차용.)
	// 하나의 이미지로 이루어진 일반 포맷들은 그냥 한 프레임만 읽어오면 됨.
	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame);

	// WIC Bitmap -> ID2DBitmap 포맷으로 변환하기 위한 변환기(converter) 생성.
	IWICFormatConverter* wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);

	// 픽셀 당 32비트 압축 픽셀 BGRA 비트맵으로 변환해주기 위해 변환기를 세팅.
	hr = wicConverter->Initialize(
			wicFrame,						// 변환해줄 비트맵
			GUID_WICPixelFormat32bppPBGRA,  // 변환할 픽셀 형식. 32bit per pixel Packed BGRA : 4바이트 int에 압축되어 들어감. 0xRRGGBBAA
			WICBitmapDitherTypeNone,        // 이미지 변환 시 사용할 dither 알고리즘.
			NULL,							// 변환 시 사용할 팔레트.
			0.0,						    // 변환 시 사용할 알파 임계값.
			WICBitmapPaletteTypeCustom      // 변환 시 사용할 팔레트 translation 타입.
	);

	// 변환기를 이용, Direct2D 비트맵을 생성해줌.
	gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(
		wicConverter,						// 변환기.
		NULL,								// D2D1_BITMAP_PROPERTIES
		&bmp								// 최종 변환된 D2D1 비트맵.
	);

	// WIC는 오직 이미지를 파일로 부터 메모리에 로드하기 위해 사용한 것이므로, D2D1Bitmap을 만들어주었으니 해제해줌.
	if (wicFactory) wicFactory->Release();
	if (wicDecoder) wicDecoder->Release();
	if (wicConverter) wicConverter->Release();
	if (wicFrame) wicFrame->Release();
}

SpriteSheet::~SpriteSheet()
{
	if (bmp) bmp->Release();
}

void SpriteSheet::Draw()
{
	// 전체 이미지를 (0,0) 위치에 그려줌.
	gfx->GetRenderTarget()->DrawBitmap(
		bmp,
		D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height),  // destination Rectangle (그려줄 공간 크기)
		1.0f,																   // opacity
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, // 보간 모드
		D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height)   // source Rectangle (그려줄 비트맵 크기)
	);
}
