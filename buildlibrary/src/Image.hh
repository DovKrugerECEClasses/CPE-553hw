#pragma once

class Image {
private:
	uint32_t width_;
	uint32_t height_;
	uint32_t *rgba;

	bool isValidPNG() const;
	bool isValidJPeg() const;
	static char* loadFile();
	void loadJPEG2000(int fh);
	void saveJPEG2000(int fh);
	void loadPNG(int fh);
	void savePNG(int fh);
	Image(uint32_t width, uint32_t height) :
		width(width), height(height), rgba(new uint32_t[width*height]) {}
public:
	Image(uint32_t width, uint32_t height, const uint32_t RGBVAL);
	Image(const char filename[]);
	~Image() {
		delete [] rgba;
	}
	Image(const Image &);
	Image& operator =(const Image &);
	Image(Image&& orig) : width(orig.width), height(orig.height), rgba(orig.rgba) {
		orig.rgba = nullptr;
	}

	bool load(const char filename[]);
	bool save(const char filename[]);

	void clear(const uint32_t RGBVAL);
	void flipHorizontal();
	void flipVertical();
	//TODO:	void resize(uint32_t w, uint32_t h);
	void copy(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t x2, uint32_t y2);

	// Image characteristics
	uint32_t	width() const { return width_; }
	uint32_t	height() const { return height_; }
	uint32_t*	getPixels() { return rgba; }
};

//! Reads an already-opened Jpeg2000 file.
void Image::loadJPEG2000(int f) {
	ILboolean		bRet;
	jas_stream_t	*Stream;

	iSetInputFile(File);
	uint32_t firstPos = itell();

	if (!JasperInit) {
		if (jas_init()) {
			ilSetError(IL_LIB_JP2_ERROR);
			return IL_FALSE;
		}
		JasperInit = IL_TRUE;
	}
	Stream = iJp2ReadStream();
	if (!Stream)
	{
		ilSetError(IL_COULD_NOT_OPEN_FILE);
		return IL_FALSE;
	}

	bool status = iLoadJp2Internal(Stream, nullptr);
	// Close the input stream.
	jas_stream_close(Stream);

	iseek(FirstPos, IL_SEEK_SET);
}

//! Reads a Jpeg2000 file.
bool Image::LoadJPEG2000(const char filename[]) {
	int	f = open(filename);
	if (!loadJPEG2000(f))
		return false;
	close(f);
}
