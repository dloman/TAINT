#include "PanelImageMaker.hpp"
#include <Images/Image.hpp>
#include <bitset>

#include <iostream>

namespace taint
{
  //---------------------------------------------------------------------------
  //---------------------------------------------------------------------------
  static void DrawTopStuff(dl::image::Image& Image)
  {
    //Draw Key
    Image.DrawCircle(60, 60, 24, {0, 0, 0});
    Image.DrawCircle(60, 60, 20, {192, 192, 192});
    Image.DrawCircle(60, 60, 14, {0, 0, 0});
    Image.DrawCircle(60, 60, 10, {192, 192, 192});
    Image.DrawLine(60, 60, 60, 50, {0, 0, 0}, 6);

    //Draw Key Light
    Image.DrawCircle(110, 60, 20, {192, 192, 192});
    Image.DrawCircle(110, 60, 14, {255, 60, 60});

    //Draw Power On
    Image.DrawCircle(220, 60, 28, {0, 0, 0});
    Image.DrawCircle(220, 60, 24, {255, 60, 60});

    //Draw Big Red Button
    Image.DrawCircle(220, 190, 66, {0, 0, 0});
    Image.DrawCircle(220, 190, 58, {255, 60, 60});

    //Draw Dial
    Image.DrawCircle(380, 160, 45, {255, 255, 255});
  }

  //---------------------------------------------------------------------------
  //---------------------------------------------------------------------------
  static void DrawRow(
    dl::image::Image& Image,
    const size_t Index,
    std::bitset<4> Values)

  {
    std::vector<uint8_t> OnColor = {255, 60, 60};
    std::vector<uint8_t> OffColor = {90, 20, 20};

    if (Index < 2)
    {
      OnColor = {60, 255, 60};
      OffColor = {20, 90, 20};
    }

    for (auto i = 0u; i < 4; ++i)
    {
      Image.DrawCircle(60 + (i * 90), 370 + (Index * 90), 28, {0, 0, 0});

      if (Values[i])
      {
        Image.DrawCircle(60 + (i * 90), 370 + (Index * 90), 24, OnColor);
      }
      else
      {
        Image.DrawCircle(60 + (i * 90), 370 + (Index * 90), 24, OffColor);
      }

      Image.DrawCircle(60 + (i * 90), 415 + (Index * 90), 8, {190, 190, 190});
      Image.DrawCircle(60 + (i * 90), 415 + (Index * 90), 6, {0, 0, 0});
      Image.DrawCircle(60 + (i * 90), 415 + (Index * 90), 4, {190, 190, 30});
    }
  }

  //---------------------------------------------------------------------------
  //---------------------------------------------------------------------------
  static void DrawColumn(
    dl::image::Image& Image,
    std::bitset<4> Values)

  {
    Image.DrawCircle(420, 370, 28, {192, 192, 192});
    Image.DrawCircle(420, 370, 24, {0, 0, 0});
    Image.DrawCircle(420, 415, 12, {192, 192, 192});
    if (Values[0])
    {
      Image.DrawLine(398, 370, 442, 370, {255, 255, 255}, 8);
      Image.DrawCircle(420, 415, 10, {100, 30, 30});
    }
    else
    {
      Image.DrawLine(420, 348, 420, 392, {255, 255, 255}, 8);
      Image.DrawCircle(420, 415, 10, {255, 60, 60});
    }

    Image.DrawCircle(420, 460, 28, {192, 192, 192});
    Image.DrawCircle(420, 460, 24, {0, 0, 0});
    Image.DrawCircle(420, 505, 12, {192, 192, 192});
    Image.DrawCircle(420, 505, 10, {255, 60, 60});

    Image.DrawCircle(420, 550, 28, {192, 192, 192});
    Image.DrawCircle(420, 550, 24, {255, 40, 40});
    Image.DrawCircle(420, 595, 12, {192, 192, 192});
    if (Values[2])
    {
      Image.DrawLine(400, 560, 442, 540, {255, 255, 255}, 8);
      Image.DrawCircle(420, 595, 10, {100, 30, 30});
    }
    else
    {
      Image.DrawLine(398, 550, 442, 550, {255, 255, 255}, 8);
      Image.DrawCircle(420, 595, 10, {255, 60, 60});
    }

    Image.DrawCircle(420, 640, 30, {255, 40, 40});
    Image.DrawCircle(420, 640, 24, {255, 255, 255});
    Image.DrawCircle(420, 640, 20, {255, 40, 40});
    Image.DrawLine(400, 625, 420, 640, {255, 40, 40}, 10);
    Image.DrawLine(442, 625, 420, 640, {255, 40, 40}, 15);

    Image.DrawLine(420, 640, 420, 670, {255, 40, 40}, 8);

    Image.DrawCircle(420, 685, 12, {192, 192, 192});
    Image.DrawCircle(420, 685, 10, {255, 60, 60});
  }

  //---------------------------------------------------------------------------
  //---------------------------------------------------------------------------
  dl::image::Image MakePanelImage(const std::array<uint8_t, 5>& Values)
  {
    dl::image::Image Image(PanelImageWidth, PanelImageHeight);

    for (size_t x = 0; x < PanelImageWidth; ++x)
    {
      for (size_t y = 0; y < PanelImageHeight; ++y)
      {
        if (
          x < 10 || x > PanelImageWidth - 10 ||
          y < 10 || y > PanelImageHeight - 10)
        {
          Image.SetPixel(x, y, {0, 0, 0});
        }
        else
        {
          Image.SetPixel(x, y, {168, 168, 168});
        }
      }
    }

    DrawTopStuff(Image);

    DrawRow(Image, 0, Values[0]);
    DrawRow(Image, 1, Values[1]);
    DrawRow(Image, 2, Values[2]);
    DrawRow(Image, 3, Values[3]);

    DrawColumn(Image, Values[4]);
    return Image;
  }
}
