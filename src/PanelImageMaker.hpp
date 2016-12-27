#pragma once

#include <memory>

namespace dl::image
{
  class Image;
}

namespace taint
{
  constexpr size_t PanelImageWidth = 480;

  constexpr size_t PanelImageHeight = 720;

  dl::image::Image MakePanelImage(const std::array<uint8_t, 5>& Values);
}
