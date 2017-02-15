#include "PanelImageMaker.hpp"

#include <Images/Bitmap.hpp>
#include <Images/Image.hpp>
#include <Tcp/Server.hpp>
#include <String/String.hpp>

#include <Requests/Requests.hpp>
#include <Http/Responce.hpp>

#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
static std::string ParseRequest(const std::string& Request)
{
  auto InputData = dl::Split(Request);

  if (InputData[0].find("GET") != std::string::npos)
  {
    std::cout << "GET!!" << std::endl;
  }
  else
  {
    std::cerr << "fuckkkk" << std::endl;
  }
  std::cout << Request << std::endl;
  return "";
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int main(int argc, const char** argv)
{
  auto Image = dl::image::CreateBitmap(taint::MakePanelImage({0, 1, 2, 3, 4}));

  try
  {
    dl::tcp::Server TcpServer(80, 1, 1);

    std::cout << "Server Listening " << std::endl;

    TcpServer.GetNewSessionSignal().Connect(
      [&Image] (std::weak_ptr<dl::tcp::Session> pWeakSession)
      {
        auto pSession = pWeakSession.lock();
        if (pSession)
        {
          pSession->GetSignalWriteError().Connect([](const asio::error_code& Error, const std::string&)
          { std::cerr << "ERROR: " << Error.message() << std::endl;});

          pSession->GetOnRxSignal().Connect(
            [pWeakSession, &Image]
            (const std::string& Bytes)
            {
              std::shared_ptr<dl::tcp::Session> pSession = pWeakSession.lock();

              if (pSession)
              {
                try
                {
                  std::this_thread::sleep_for(std::chrono::milliseconds(100));

                  ParseRequest(Bytes);

                  std::stringstream Stream;

                   std::time_t Time = std::time(nullptr);
                   std::tm LocalTime = *std::localtime(&Time);

                   Stream <<
                    "HTTP/1.1 200 OK\r\n" <<
                    "Date: " << std::put_time(&LocalTime, "%c") << "\r\n" <<
                    "Server: Apache/2.4.23\r\n" <<
                    "Accept-Ranges: bytes\r\n" <<
                    "Content-Length: " << Image.size() << "\r\n" <<
                    "Connection: close\r\n" <<
                    "Content-Type: image/bmp\r\n\r\n" <<
                   Image;

                  pSession->Write(Stream.str());

                }
                catch(std::exception& Exception)
                {
                  std::cerr << "ERROR: " << Exception.what();
                }
              }
            });
        }
      });

    while (true)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
  }
  catch(const std::exception& Exception)
  {
    std::cerr << "ERROR: " << Exception.what() << std::endl;
  }
    return 0;
}
