#include <iostream>
#include <string>
#include "bitmap.h"
#include <vector>
#include <cstdlib>

using namespace std;

bool goodImage(string);
void OverlayImages();

int MaxImages = 10;

int imageCount;

string imgName;

Bitmap image;
Pixel rgb;

vector < vector <vector <Pixel> > > bmp;

int main()
{
    bmp.resize(1);
    for(int i = 0; i < MaxImages;)
    {
        cout << "Enter the name of the file you would like to add." << endl;
        cin >> imgName;
        
        if(imgName == "Done" || imgName == "done" || imgName == "DONE")
        {
            if(i <= 1)
            {
                cout << "You need to enter two or more images" << endl;
                return 0;
            }
            i = MaxImages;
        }
        else
        {
            image.open(imgName);
        }
       
        
            
            if(imgName[imgName.length() - 4] == '.' && imgName[imgName.length() - 3] == 'b' && imgName[imgName.length() - 2] == 'm' && imgName[imgName.length() - 1] == 'p' && image.isImage() && i != MaxImages)
           {
        
                if(i == 0)
                {
        
                    bmp[i] = image.toPixelMatrix();
                    i++;
                    bmp.resize(i + 1);
                }
                else
                {
                        
                    bmp[i] = image.toPixelMatrix();
        
                    if(bmp[0].size() == bmp[i].size() && bmp[0][0].size() == bmp[i][0].size())
                    {
                        i++;
                        bmp.resize(i + 1);
                    }
                    else
                    {
                        cout << "Wrong dimensions" << endl;
        
                    }
                }
            }
            else if(i != MaxImages)
            {
                cout << "File is not valid.\n";
            }
        
    }

    OverlayImages();

    cout << "What name would you like to save this image with." << endl;
    cin >> imgName;

    image.save(imgName + ".bmp");

}

void OverlayImages()
{
    
    double pixelAvg = 0;
    int RedSum = 0;
    int GreenSum = 0;
    int BlueSum = 0;
    int progress = 0;
    int quarterSize = bmp[0].size() / 4;

    for(int r = 0; r < bmp[0].size(); r++)
    {
        for(int c = 0; c < bmp[0][0].size(); c++)
        {
            for(int i = 0; i < bmp.size() - 1; i++)
            {
                
              rgb = bmp[i][r][c];

              RedSum += rgb.red;
              GreenSum += rgb.green;
              BlueSum += rgb.blue;
              
            }

            rgb.red = RedSum / bmp.size();
            rgb.green = GreenSum / bmp.size();
            rgb.blue = BlueSum / bmp.size();
            
            
            RedSum = 0;
            GreenSum = 0;
            BlueSum = 0;

            bmp[0][r][c] = rgb;
           
        }

        if(r % quarterSize == 0 && progress != 3)
        {
    
            progress++;
            cout << "Image composition is " << progress << " quarters complete." << endl;

        }
    }
    
    image.fromPixelMatrix(bmp[0]);
     
}

