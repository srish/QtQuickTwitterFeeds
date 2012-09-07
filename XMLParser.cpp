#include "XMLParser.h"
#include <QDebug>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QDomNode>
#include <QDomElement>
#include <QDomDocument>
#include <QNetworkAccessManager>

#include <QStringList>#include <QApplication>


struct XMLParserData
{
    QStringList tweetList;
    QNetworkAccessManager* manager;
};

XMLParser::XMLParser(QObject* parent)
{
    d = new XMLParserData;
}

XMLParser::~XMLParser()
{
    delete d;
}

XMLParser& XMLParser::instance()
{
    static XMLParser theInstance;
    return theInstance;
}

void XMLParser::parseTweets(QString twitterID)
{
    QString id = twitterID;

    if(id.isEmpty())
        return;

    QUrl url = QString("http://api.twitter.com/1/statuses/user_timeline.xml?screen_name=%1").arg(id);

    //QUrl url = QString("https://graph.facebook.com/me?access_token=");

    QNetworkRequest request(url);
    d->manager = new QNetworkAccessManager(this);
    QNetworkReply* reply = d->manager->get(request);

    connect(reply, SIGNAL(finished()) , this , SLOT(callDone()));
}

void XMLParser::callDone()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(this->sender());

    if(!reply)
        return;

    QDomDocument doc;
    doc.setContent(reply->readAll());

    QDomElement docRootElement = doc.documentElement();

    QDomNode n = docRootElement.firstChild();

    for(QDomNode n = docRootElement.firstChild(); !n.isNull(); n= n.nextSibling())
    {
        qDebug() << n.firstChildElement("text").text();
        d->tweetList.prepend(n.firstChildElement("text").text());
    }

   // qDebug() << d->tweetList;
}
