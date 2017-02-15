#include "PanelImageMaker.hpp"
#include <Images/Image.hpp>
#include <Images/Bitmap.hpp>
#include <iostream>
#include <random>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(int argc, const char** argv)
{

  std::random_device RandomDevice;
  std::mt19937 Generator(RandomDevice());
  std::uniform_int_distribution<uint8_t> UniformDistribution(0, 255);

  auto Image = taint::MakePanelImage({
    UniformDistribution(Generator),
    UniformDistribution(Generator),
    UniformDistribution(Generator),
    UniformDistribution(Generator),
    UniformDistribution(Generator)});

  dl::image::SaveBitmap(Image, "Panel.bmp");

  return 0;
}
