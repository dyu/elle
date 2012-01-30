//
// ---------- header ----------------------------------------------------------
//
// project       plasma/updater
//
// license       infinit
//
// author        Raphael Londeix   [Mon 30 Jan 2012 12:41:48 PM CET]
//

//
// ---------- includes --------------------------------------------------------
//

#include <cassert>
#include <iostream>

#include "plasma/common/resources.hh"

#include "Application.hh"

using namespace plasma::updater;

//
// ---------- constructors & destructors --------------------------------------
//

Application::Application(int ac, char** av) :
  QApplication(ac, av, false),
  _network_access_manager(0),
  _has_list(false),
  _release_reader()
{}

Application::~Application()
{
  delete this->_network_access_manager;
  this->_network_access_manager = 0;
}

//
// ---------- methods ---------------------------------------------------------
//

int Application::Exec()
{
  this->_network_access_manager = new QNetworkAccessManager(this);
  this->connect(
      this->_network_access_manager,
      SIGNAL(finished(QNetworkReply*)),
      SLOT(_OnDownloadFinished(QNetworkReply*))
  );
  std::cout << "Checking out " << INFINIT_RELEASE_URI << std::endl;
  auto reply = this->_network_access_manager->get(
      QNetworkRequest(QUrl(INFINIT_RELEASE_URI))
  );

  this->connect(
      reply, SIGNAL(error(QNetworkReply::NetworkError)),
      this, SLOT(_OnDownloadError(QNetworkReply::NetworkError))
  );

  return this->exec();
}

void Application::_OnDownloadFinished(QNetworkReply* reply)
{
  assert(reply != 0);
  if (reply->error() == QNetworkReply::NoError)
    {
      bool result;

      if (this->_has_list)
        result = this->_ProcessResource(*reply);
      else
        result = this->_ProcessResourceList(*reply);
      if (!result)
        this->quit();
      if (this->_release_reader.files.size() > 0)
        this->_DownloadNextResource();
      else
        {
          std::cout << "All release files downloaded successfully\n";
          // end checks here
          this->quit();
        }
    }
  else
    {
      std::cerr << "An error occured, ignoring further replies\n";
    }
  reply->deleteLater();
}

void Application::_DownloadNextResource()
{
  assert(this->_release_reader.files.size() > 0);
  auto& file = this->_release_reader.files.front();
  QString uri = QString(INFINIT_BASE_URL "/") + QString(file.relpath.c_str());
  std::cout << "Checking out " << uri.toStdString() << std::endl;
  auto reply = this->_network_access_manager->get(
      QNetworkRequest(QUrl(uri))
  );
  this->connect(
      reply, SIGNAL(error(QNetworkReply::NetworkError)),
      this, SLOT(_OnDownloadError(QNetworkReply::NetworkError))
  );
}

void Application::_OnDownloadError(QNetworkReply::NetworkError error)
{
  std::cout << "Got error code = " << error << std::endl;
  this->exit(1);
}

bool Application::_ProcessResource(QNetworkReply& reply)
{
  assert(this->_has_list);
  assert(this->_release_reader.files.size() > 0);
  auto& file = this->_release_reader.files.front();
  std::cout << "Just downloaded " << file.relpath << std::endl;
  // XXX write the file here
  this->_release_reader.files.pop();
  return true;
}

bool Application::_ProcessResourceList(QNetworkReply& reply)
{
  assert(!this->_has_list);
  if (!this->_release_reader.Feed(reply.readAll()))
    return false;
  this->_has_list = true;
  return true;
}
