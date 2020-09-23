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
            class PPMObjectElement {
                public:
                    PPMObjectElement &operator=(char rhs){
                        val_ = rhs;
                        return *this;
                    }
                private:
                    char val_ = ' ';
            };
            PPMObjectElement &operator[](size_t i){
                return element_[i];
            }
            PPMObjectElement element_[10];
        };
};
