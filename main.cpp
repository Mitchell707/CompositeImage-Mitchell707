#include<iostream>
#include<string>
#include"bitmap.h"
#include<vector>
#include<cstdlib>

using namespace std;

bool goodImage(string);
void OverlayImages();

bool done = false;

int MaxImages = 10;

int imageCount;
string imgName;

Bitmap image;
Pixel rgb;

vector < vector <vector <Pixel> > > bmp;

//Make the user input the image names, checking if each one is in a proper format
//load the ones that are legitimate, have the same size as the first image and are .bmp into an array of vectors saved from the bitmap

//OverlayImage
    //Make a nested for loop like you would with an array but have another one in the center to get the image you want from the index
    //Get image[index][row][col]
    //get each pixel rgb value and divide it by the number of images
    //set the pixel in the first image as that
    //ask the user what's the name they want to save it as

//Print out every quarter of the rows are started

//functions
    //check image for errors
        //if the image ends in .bmp
        //if the length of the row and column are equal to the first image
        //return true
        //report an error for wrong size or type

int main()
{
    for(int i = 0; i < MaxImages;)
    {
        cout << "Enter the name of the file you would like to add.\n";
        cin >> imgName;

        image.open(imgName);
        
        if(imgName[imgName.length() - 4] == '.' && imgName[imgName.length() - 3] == 'b' && imgName[imgName.length() - 2] == 'm' && imgName[imgName.length() - 1] == 'p'/* &&
         image.isImage() != 0*/)
         {
            if(i > 0)
            {
                bmp[i] = image.toPixelMatrix();
                i++;
                
            }
            else if(bmp[0].size() == bmp[i].size() && bmp[0][0].size() == bmp[i][0].size())
            {
                bmp[i] = image.toPixelMatrix();
                i++;
                
            }
            else
            {
                cout << "Wrong dimensions.";
            }
         }
         else if(imgName == "DONE" || imgName == "Done" || imgName == "done")
         {
            i = MaxImages;
         }
         else
         {
            cout << "File is not valid.\n";
         }
    }

    OverlayImages();

    cout << "What name would you like to save this image with.\n";
    cin >> imgName;

    image.save(imgName + ".bmp");

}


bool goodImage(string imageString)
{



}

void OverlayImages()
{
    
    double pixelAvg = 0;
    int RedSum = 0;
    int GreenSum = 0;
    int BlueSum = 0;

    for(int r = 0; r < bmp[0].size(); r++)
    {
        for(int c = 0; c < bmp[0][0].size(); c++)
        {
            for(int i = 0; i < bmp.size(); i++)
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
    }

    image.fromPixelMatrix(bmp[0]);
}

