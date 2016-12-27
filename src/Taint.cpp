#include "PanelImageMaker.hpp"
#include <Images/Image.hpp>
#include <Images/Bitmap.hpp>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(int argc, const char** argv)
{
  auto Image = taint::MakePanelImage({1u, 2u, 3u, 4u, 5u});

  dl::image::SaveBitmap(Image, "Panel.bmp");

  return 0;
}
