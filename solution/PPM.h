#include <string>

class PPM{
    public:
        struct Pixel{
            unsigned char rgb[3];
        };
        struct Bin{
            unsigned char pix[3];
        };
        struct PPMObject{
            Pixel * mPixels = nullptr;
            Bin * mBins = nullptr;
            unsigned int mRow;
            unsigned int mCol;
            unsigned int mMax;
            unsigned int size;
            std::string PType;
            char operator[] (int index){
                return *mPixels->rgb;
            }
        };
};
