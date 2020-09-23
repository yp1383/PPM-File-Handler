#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <exception>
#include <algorithm>
#include "boost/algorithm/clamp.hpp"
#include "PPM.h"

PPM::PPMObject *readPPM(const std::string &filename){
    try{
        std::ifstream input;
        input.open(filename, std::ios::binary | std::ios::in);
        PPM::PPMObject * image = new PPM::PPMObject();
        input >> image->PType;
        input >> image->mRow >> image->mCol >> image->mMax;
        image->size = image->mCol * image->mRow;
        if(image->PType.compare("P3") == 0){
            image->mPixels = new PPM::Pixel [image->size];
            for(int i = 0; i < image->size; i ++){
                unsigned int r,g,b;
                input >> r >> g >> b;
                image->mPixels[i].rgb[0] = static_cast<unsigned char>(r);
                image->mPixels[i].rgb[1] = static_cast<unsigned char>(g);
                image->mPixels[i].rgb[2] = static_cast<unsigned char>(b);
            }
        }
        else if(image->PType.compare("P6") == 0){
            image->mBins = new PPM::Bin [image->size];
            for(int i = 0; i < image->size; i ++){
                input.read((char*) &image->mBins[i].pix[0], sizeof(unsigned char));
                input.read((char*) &image->mBins[i].pix[1], sizeof(unsigned char));
                input.read((char*) &image->mBins[i].pix[2], sizeof(unsigned char));
            }
        }
        else if(image->PType.compare("P2") == 0){
            image->mPixels = new PPM::Pixel [image->size];
            for(int i = 0; i < image->size; i ++){
                unsigned int r;
                input >> r;
                image->mPixels[i].rgb[0] = static_cast<unsigned char>(r);
            }
        }
        else if(image->PType.compare("P5") == 0){
            image->mBins = new PPM::Bin [image->size];
            for(int i = 0; i < image->size; i ++){
                input.read((char*) &image->mBins[i].pix[0], sizeof(unsigned char));
            }
        }
        input.close();
        return image;
    }catch(std::exception& e){
        std::cout << "Error: " << e.what() << std::endl;
        return 0;
    }
}


void savePPM(const std::string &filename, const PPM::PPMObject &ppmFile){
    try{
        std::ofstream savePPMFile(filename, std::ofstream::trunc);
        savePPMFile << ppmFile.PType << "\n"
            << ppmFile.mRow << " " << ppmFile.mCol << "\n"
            << ppmFile.mMax << "\n";
        if(ppmFile.PType.compare("P3") == 0){
            for(int i = 0; i < ppmFile.size; i ++){
                savePPMFile << static_cast<unsigned int>(ppmFile.mPixels[i].rgb[0]) << std::endl;
                savePPMFile << static_cast<unsigned int>(ppmFile.mPixels[i].rgb[1]) << std::endl;
                savePPMFile << static_cast<unsigned int>(ppmFile.mPixels[i].rgb[2]) << std::endl;
            }
        }
        else if(ppmFile.PType.compare("P6") == 0){
            for(int i = 0; i < ppmFile.size; i ++){
                savePPMFile.write((char*) &ppmFile.mBins[i].pix[0], sizeof(unsigned char));
                savePPMFile.write((char*) &ppmFile.mBins[i].pix[1], sizeof(unsigned char));
                savePPMFile.write((char*) &ppmFile.mBins[i].pix[2], sizeof(unsigned char));
            }
        }
        else if(ppmFile.PType.compare("P2") == 0){
            for(int i = 0; i < ppmFile.size; i ++){
                savePPMFile << static_cast<unsigned int>(ppmFile.mPixels[i].rgb[0]) << std::endl;
            }
        }
        else if(ppmFile.PType.compare("P5") == 0){
            for(int i = 0; i < ppmFile.size; i ++){
                savePPMFile.write((char*) &ppmFile.mBins[i].pix[0], sizeof(unsigned char));
            }
        }
        savePPMFile.close();
    }catch(std::exception& e){
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void addPPM(const std::string &filename, const PPM::PPMObject &image1, const PPM::PPMObject &image2){
    try{
        std::ofstream savePPMFile(filename, std::ofstream::trunc);
        savePPMFile << image1.PType << "\n"
            << image1.mRow << " " << image1.mCol << "\n"
            << image1.mMax << "\n";
        if(image1.PType.compare("P3") == 0){
            for(int i = 0; i < image1.size; i ++){
                savePPMFile << static_cast<unsigned int>(image1.mPixels[i].rgb[0])  + static_cast<unsigned int>(image2.mPixels[i].rgb[0])<< std::endl;
                savePPMFile << static_cast<unsigned int>(image1.mPixels[i].rgb[1])  + static_cast<unsigned int>(image2.mPixels[i].rgb[1])<< std::endl;
                savePPMFile << static_cast<unsigned int>(image1.mPixels[i].rgb[2])  + static_cast<unsigned int>(image2.mPixels[i].rgb[2])<< std::endl;
            }
        }
        else if(image1.PType.compare("P6") == 0){
            for(int i = 0; i < image1.size; i ++){
                char a = image1.mBins[i].pix[0] + image2.mBins[i].pix[0];
                char b = image1.mBins[i].pix[1] + image2.mBins[i].pix[1];
                char c = image1.mBins[i].pix[2] + image2.mBins[i].pix[2];
                savePPMFile.write((char*) &a , sizeof(unsigned char));
                savePPMFile.write((char*) &b , sizeof(unsigned char));
                savePPMFile.write((char*) &c , sizeof(unsigned char));
            }
        }
        else if(image1.PType.compare("P2") == 0){
            for(int i = 0; i < image1.size; i ++){
                savePPMFile << static_cast<unsigned int>(image1.mPixels[i].rgb[0])  + static_cast<unsigned int>(image2.mPixels[i].rgb[0])<< std::endl;
            }
        }
        else if(image1.PType.compare("P5") == 0){
            for(int i = 0; i < image1.size; i ++){
                char a = image1.mBins[i].pix[0] + image2.mBins[i].pix[0];
                savePPMFile.write((char*) &a, sizeof(unsigned char));
            }
        }
        savePPMFile.close();
    }catch(std::exception& e){
        std::cout << "Error: " << e.what() << std::endl;
    }    
}

void additionPPM(const std::string &filename, const PPM::PPMObject &image1, const PPM::PPMObject &image2){
    try{
        std::ofstream savePPMFile(filename, std::ofstream::trunc);
        savePPMFile << image1.PType << "\n"
            << image1.mRow << " " << image1.mCol << "\n"
            << image1.mMax << "\n";
        if(image1.PType.compare("P3") == 0){
            for(int i = 0; i < image1.size; i ++){
                savePPMFile << static_cast<unsigned int>(image1.mPixels[i].rgb[0]) / 2 + static_cast<unsigned int>(image2.mPixels[i].rgb[0]) / 2 << std::endl;
                savePPMFile << static_cast<unsigned int>(image1.mPixels[i].rgb[1]) / 2 + static_cast<unsigned int>(image2.mPixels[i].rgb[1]) / 2<< std::endl;
                savePPMFile << static_cast<unsigned int>(image1.mPixels[i].rgb[2]) / 2 + static_cast<unsigned int>(image2.mPixels[i].rgb[2]) / 2<< std::endl;
            }
        }
        else if(image1.PType.compare("P6") == 0){
            for(int i = 0; i < image1.size; i ++){
                char a = image1.mBins[i].pix[0] / 2 + image2.mBins[i].pix[0] / 2;
                char b = image1.mBins[i].pix[1] / 2 + image2.mBins[i].pix[1] / 2;
                char c = image1.mBins[i].pix[2] / 2 + image2.mBins[i].pix[2] / 2;
                savePPMFile.write((char*) &a, sizeof(unsigned char));
                savePPMFile.write((char*) &b, sizeof(unsigned char));
                savePPMFile.write((char*) &c, sizeof(unsigned char));
            }
        }
        else if(image1.PType.compare("P2") == 0){
            for(int i = 0; i < image1.size; i ++){
                savePPMFile << static_cast<unsigned int>(image1.mPixels[i].rgb[0]) / 2  + static_cast<unsigned int>(image2.mPixels[i].rgb[0]) / 2<< std::endl;
            }
        }
        else if(image1.PType.compare("P5") == 0){
            for(int i = 0; i < image1.size; i ++){
                char a = image1.mBins[i].pix[0] / 2 + image2.mBins[i].pix[0] / 2;
                savePPMFile.write((char*) &a , sizeof(unsigned char));
            }
        }
        savePPMFile.close();
    }catch(std::exception& e){
        std::cout << "Error: " << e.what() << std::endl;
    }  
}

void subtractPPM(const std::string &filename, const PPM::PPMObject &image1, const PPM::PPMObject &image2){
    try{
        std::ofstream savePPMFile(filename, std::ofstream::trunc);
        savePPMFile << image1.PType << "\n"
            << image1.mRow << " " << image1.mCol << "\n"
            << image1.mMax << "\n";
        if(image1.PType.compare("P3") == 0){
            for(int i = 0; i < image1.size; i ++){
//              std::clamp is not working on my pc,so I include boost::algorithm 
//              can use boost::algorithm::clamp to replace std::clamp
                savePPMFile << std::clamp(static_cast<__int16_t>(image1.mPixels[i].rgb[0]) - static_cast<__int16_t>(image2.mPixels[i].rgb[0]), 0, image1.mMax) << std::endl;
                savePPMFile << std::clamp(static_cast<__int16_t>(image1.mPixels[i].rgb[1]) - static_cast<__int16_t>(image2.mPixels[i].rgb[1]), 0, image1.mMax) << std::endl;
                savePPMFile << std::clamp(static_cast<__int16_t>(image1.mPixels[i].rgb[2]) - static_cast<__int16_t>(image2.mPixels[i].rgb[2]), 0, image1.mMax) << std::endl;
            }
        }
        else if(image1.PType.compare("P6") == 0){
            for(int i = 0; i < image1.size; i ++){
                char a = image1.mBins[i].pix[0] - image2.mBins[i].pix[0];
                char b = image1.mBins[i].pix[1] - image2.mBins[i].pix[1];
                char c = image1.mBins[i].pix[2] - image2.mBins[i].pix[2];
                savePPMFile.write((char*) &a, sizeof(unsigned char));
                savePPMFile.write((char*) &b, sizeof(unsigned char));
                savePPMFile.write((char*) &c, sizeof(unsigned char));
            }
        }
        else if(image1.PType.compare("P2") == 0){
            for(int i = 0; i < image1.size; i ++){
                savePPMFile << std::clamp(static_cast<__int16_t>(image1.mPixels[i].rgb[0]) - static_cast<__int16_t>(image2.mPixels[i].rgb[0]), 0, image1.mMax) << std::endl;
            }
        }
        else if(image1.PType.compare("P5") == 0){
            for(int i = 0; i < image1.size; i ++){
                char a = image1.mBins[i].pix[0] - image2.mBins[i].pix[0];
                savePPMFile.write((char*) &a , sizeof(unsigned char));
            }
        }
        savePPMFile.close();
    }catch(std::exception& e){
        std::cout << "Error: " << e.what() << std::endl;
    } 
}

void multiByScalePPM(const std::string &filename, const PPM::PPMObject &image, float scale){
    try{
        std::ofstream savePPMFile(filename, std::ofstream::trunc);
        savePPMFile << image.PType << "\n"
            << image.mRow << " " << image.mCol << "\n"
            << image.mMax << "\n";
        if(image.PType.compare("P3") == 0){
            for(int i = 0; i < image.size; i ++){
                unsigned int r = static_cast<unsigned int>((float)image.mPixels[i].rgb[0] * scale);
                unsigned int g = static_cast<unsigned int>((float)image.mPixels[i].rgb[1] * scale);
                unsigned int b = static_cast<unsigned int>((float)image.mPixels[i].rgb[2] * scale);
                savePPMFile << r << std::endl;
                savePPMFile << g << std::endl;
                savePPMFile << b << std::endl;
            }
        }
        else if(image.PType.compare("P6") == 0){
            for(int i = 0; i < image.size; i ++){
                char a = image.mBins[i].pix[0] * scale;
                char b = image.mBins[i].pix[1] * scale;
                char c = image.mBins[i].pix[2] * scale;
                savePPMFile.write((char*) &a, sizeof(unsigned char));
                savePPMFile.write((char*) &b, sizeof(unsigned char));
                savePPMFile.write((char*) &c, sizeof(unsigned char));
            }
        }
        else if(image.PType.compare("P2") == 0){
            for(int i = 0; i < image.size; i ++){
                unsigned int r = static_cast<unsigned int>((float)image.mPixels[i].rgb[0] * scale);
                savePPMFile << r << std::endl;
            }
        }
        else if(image.PType.compare("P5") == 0){
            for(int i = 0; i < image.size; i ++){
                char a = image.mBins[i].pix[0] * scale;
                savePPMFile.write((char*) &a, sizeof(unsigned char));
            }
        }
        savePPMFile.close();
    }catch(std::exception& e){
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void aplhaCompositingPPM(const std::string &filename, const PPM::PPMObject &image1, float alpha1, const PPM::PPMObject &image2, float alpha2){
    try{
        if((int)(alpha1 + alpha2) != 1){
            std::cout << "Scale total should be 1" << std::endl;
            return;
        }
        std::ofstream savePPMFile(filename, std::ofstream::trunc);
        savePPMFile << image1.PType << "\n"
            << image1.mRow << " " << image1.mCol << "\n"
            << image1.mMax << "\n";
        if(image1.PType.compare("P3") == 0){
            for(int i = 0; i < image1.size; i ++){
                unsigned int r = static_cast<unsigned int>((float)image1.mPixels[i].rgb[0] * alpha1 + (float)image2.mPixels[i].rgb[0] * alpha2);
                unsigned int g = static_cast<unsigned int>((float)image1.mPixels[i].rgb[1] * alpha1 + (float)image2.mPixels[i].rgb[1] * alpha2);
                unsigned int b = static_cast<unsigned int>((float)image1.mPixels[i].rgb[2] * alpha1 + (float)image2.mPixels[i].rgb[2] * alpha2);
                savePPMFile << r << std::endl;
                savePPMFile << g << std::endl;
                savePPMFile << b << std::endl;
            }
        }
        else if(image1.PType.compare("P6") == 0){
            for(int i = 0; i < image1.size; i ++){
                char a = image1.mBins[i].pix[0] * alpha1 + image2.mBins[i].pix[0] * alpha2;
                char b = image1.mBins[i].pix[1] * alpha1 + image2.mBins[i].pix[1] * alpha2;
                char c = image1.mBins[i].pix[2] * alpha1 + image2.mBins[i].pix[2] * alpha2;
                savePPMFile.write((char*) &a, sizeof(unsigned char));
                savePPMFile.write((char*) &b, sizeof(unsigned char));
                savePPMFile.write((char*) &c, sizeof(unsigned char));
            }
        }
        else if(image1.PType.compare("P2") == 0){
            for(int i = 0; i < image1.size; i ++){
                unsigned int r = static_cast<unsigned int>((float)image1.mPixels[i].rgb[0] * alpha1 + (float)image2.mPixels[i].rgb[0] * alpha2);
                savePPMFile << r << std::endl;
            }
        }
        else if(image1.PType.compare("P5") == 0){
            for(int i = 0; i < image1.size; i ++){
                char a = image1.mBins[i].pix[0] * alpha1 + image2.mBins[i].pix[0] * alpha2;
                savePPMFile.write((char*) &a , sizeof(unsigned char));
            }
        }
        savePPMFile.close();
    }catch(std::exception& e){
        std::cout << "Error: " << e.what() << std::endl;
    } 
}

void gamma_corrected(const float gamma, PPM::PPMObject & ppmFile) {
    try{
        if(ppmFile.PType.compare("P3") == 0){
            for(auto i = 0; i < ppmFile.size; i ++ ){
                ppmFile.mPixels[i].rgb[0] = static_cast<unsigned char>(
                    pow(static_cast<float>(ppmFile.mPixels[i].rgb[0]) / static_cast<float>(ppmFile.mMax), gamma) * 
                    static_cast<float>(ppmFile.mMax));
                ppmFile.mPixels[i].rgb[1] = static_cast<unsigned char>(
                    pow(static_cast<float>(ppmFile.mPixels[i].rgb[1]) / static_cast<float>(ppmFile.mMax), gamma) * 
                    static_cast<float>(ppmFile.mMax));
                ppmFile.mPixels[i].rgb[2] = static_cast<unsigned char>(
                    pow(static_cast<float>(ppmFile.mPixels[i].rgb[2]) / static_cast<float>(ppmFile.mMax), gamma) * 
                    static_cast<float>(ppmFile.mMax));
            }
        }
        else if(ppmFile.PType.compare("P6") == 0){
            for(int i = 0; i < ppmFile.size; i ++){
                ppmFile.mBins[i].pix[0] = static_cast<unsigned char>(
                    pow(ppmFile.mBins[i].pix[0] / static_cast<float>(ppmFile.mMax), gamma) * 
                    static_cast<float>(ppmFile.mMax));
                ppmFile.mBins[i].pix[1] = static_cast<unsigned char>(
                    pow(ppmFile.mBins[i].pix[1] / static_cast<float>(ppmFile.mMax), gamma) * 
                    static_cast<float>(ppmFile.mMax));
                ppmFile.mBins[i].pix[2] = static_cast<unsigned char>(
                    pow(ppmFile.mBins[i].pix[2] / static_cast<float>(ppmFile.mMax), gamma) * 
                    static_cast<float>(ppmFile.mMax));
            }
        }
        else if(ppmFile.PType.compare("P2") == 0){
            for(auto i = 0; i < ppmFile.size; i ++ ){
                ppmFile.mPixels[i].rgb[0] = static_cast<unsigned char>(
                    pow(ppmFile.mPixels[i].rgb[0] / static_cast<float>(ppmFile.mMax), gamma) * 
                    static_cast<float>(ppmFile.mMax));
            }
        }
        else if(ppmFile.PType.compare("P5") == 0){
            for(int i = 0; i < ppmFile.size; i ++){
                ppmFile.mBins[i].pix[0] = static_cast<unsigned char>(
                    pow(ppmFile.mBins[i].pix[0] / static_cast<float>(ppmFile.mMax), gamma) * 
                    static_cast<float>(ppmFile.mMax));
            }
        }
    }catch(std::exception& e){
        std::cout << "Error: " << e.what() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    PPM::PPMObject * image1 = readPPM(std::string("../Mandrill.ppm"));
    PPM::PPMObject * image2 = readPPM(std::string("../tandon_stacked_color.ppm"));
    // Add Function:
    addPPM("add.ppm", *image1, *image2);

    // Addition Function:
    additionPPM("addition.ppm", *image1, *image2);

    // Subtract Function:
    subtractPPM("subtract.ppm", *image1, *image2);

    // MultiByScale Function:
    multiByScalePPM("multi.ppm", *image1, 0.7);

    // Alpha Compsiting Function:
    aplhaCompositingPPM("alpha.ppm", *image1, 0.7, *image2, 0.3);

    // Gamma Correction Function:
    gamma_corrected(4.f, *image1);
    savePPM("Gamma_Corrected_4.ppm", *image1);
    gamma_corrected(0.25f, *image1);
    savePPM("Gamma_Corrected_025.ppm", *image1);
    gamma_corrected(0.25f, *image1);
    savePPM("Gamma_Corrected_025_again.ppm", *image1);

    // Bracket Operator:
    char a = image1[0][0];
    std::cout << a;
    return 0;
}
