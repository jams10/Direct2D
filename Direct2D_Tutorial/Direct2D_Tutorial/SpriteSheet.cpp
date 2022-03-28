#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(const wchar_t* filename, Graphics* gfx)
{
	// �ʱ�ȭ
	this->gfx = gfx;
	bmp = NULL;
	HRESULT hr;

	// WIC ���丮 ����
	IWICImagingFactory* wicFactory = NULL;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,	// �츮�� ����� �� ������Ʈ�� Ŭ���� ���̵�.
		NULL,						
		CLSCTX_INPROC_SERVER,       // ������Ʈ�� ���� ���ؽ�Ʈ ����. ������ ���μ����� ������.
		IID_IWICImagingFactory,     // ������Ʈ�� ��ȣ�ۿ��� �������̽��� ID
		(LPVOID*)&wicFactory        // 4��° �Ű������� �ѱ� IID�� �ش��ϴ� �������̽��� �̰����� �Ѿ��.
	);

	// ���ڴ� ����
	IWICBitmapDecoder* wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
			filename,                         // ���� �̸�
			NULL,							  // ��ȣ decoder vendor
			GENERIC_READ,					  // ���� ������ �б�� ��.
			WICDecodeMetadataCacheOnLoad,     // decoder�� �ε�� �� metadata�� ĳ��.
			&wicDecoder                       // decoder�� ���� ������.
	);

	// �̹����� ���� �� �������� �о��.(gif ���ϵ��� ���� ���������� �̷���� �ֱ� ������ �̷� ����� ����.)
	// �ϳ��� �̹����� �̷���� �Ϲ� ���˵��� �׳� �� �����Ӹ� �о���� ��.
	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame);

	// WIC Bitmap -> ID2DBitmap �������� ��ȯ�ϱ� ���� ��ȯ��(converter) ����.
	IWICFormatConverter* wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);

	// �ȼ� �� 32��Ʈ ���� �ȼ� BGRA ��Ʈ������ ��ȯ���ֱ� ���� ��ȯ�⸦ ����.
	hr = wicConverter->Initialize(
			wicFrame,						// ��ȯ���� ��Ʈ��
			GUID_WICPixelFormat32bppPBGRA,  // ��ȯ�� �ȼ� ����. 32bit per pixel Packed BGRA : 4����Ʈ int�� ����Ǿ� ��. 0xRRGGBBAA
			WICBitmapDitherTypeNone,        // �̹��� ��ȯ �� ����� dither �˰���.
			NULL,							// ��ȯ �� ����� �ȷ�Ʈ.
			0.0,						    // ��ȯ �� ����� ���� �Ӱ谪.
			WICBitmapPaletteTypeCustom      // ��ȯ �� ����� �ȷ�Ʈ translation Ÿ��.
	);

	// ��ȯ�⸦ �̿�, Direct2D ��Ʈ���� ��������.
	gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(
		wicConverter,						// ��ȯ��.
		NULL,								// D2D1_BITMAP_PROPERTIES
		&bmp								// ���� ��ȯ�� D2D1 ��Ʈ��.
	);

	// WIC�� ���� �̹����� ���Ϸ� ���� �޸𸮿� �ε��ϱ� ���� ����� ���̹Ƿ�, D2D1Bitmap�� ������־����� ��������.
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
	// ��ü �̹����� (0,0) ��ġ�� �׷���.
	gfx->GetRenderTarget()->DrawBitmap(
		bmp,
		D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height),  // destination Rectangle (�׷��� ���� ũ��)
		1.0f,																   // opacity
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, // ���� ���
		D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height)   // source Rectangle (�׷��� ��Ʈ�� ũ��)
	);
}
