#include "song.h"
#include <QStringList>
#include <QRegularExpression>
#include <QFile>

namespace syncLib{

static const QStringList ValidSongs = {".mp3", ".wav", ".ogg"};
SongHeader::SongHeader()
{
    this->isSelected = false;
    this->id = -1;
    this->name = "";
    this->size = 0;
}

bool SongHeader::getName(QString & name, const QUrl &url) const {
    if(url.isLocalFile() && url.isValid()){
        name = url.fileName();
        name = name.right(name.lastIndexOf(QRegularExpression("[\\\/]")));
        return true;
    }

    return false;

}

SongHeader& SongHeader::operator =(const SongHeader& right){
    this->id = right.id;
    this->name = right.name;
    this->size = right.size;
    return *this;
}

SongHeader& SongHeader::operator =(const QMediaContent& right){
    this->id = -1;
    if(!getName(name, right.canonicalUrl())){
        name.clear();
    }
    this->size = right.canonicalResource().dataSize();
    return *this;
}

bool SongHeader::operator ==(const SongHeader& right){
    return this->name == right.name && this->size == right.size;
}

bool SongHeader::operator ==(const QMediaContent& right){
    QString name;
    if(!getName(name, right.canonicalUrl())){
        return false;
    }
    return this->name == name && this->size == right.canonicalResource().dataSize();
}

bool SongHeader::isNameValid() const{
    bool CheckSongs = false;
    for (QString i: ValidSongs){
        CheckSongs = CheckSongs || name.endsWith(i);
    }
    return CheckSongs;
}

bool SongHeader::isValid() const{

    return id > -1 && !name.isEmpty() && size > 0 && isNameValid();

}

SongHeader::~SongHeader(){}

QDataStream& operator << (QDataStream& stream, const SongHeader& song){
    stream << song.id;
    stream << song.name;
    stream << song.size;
    return stream;
}
QDataStream& operator >> (QDataStream& stream, SongHeader& song){
    stream >> song.id;
    stream >> song.name;
    stream >> song.size;
    return stream;
}


SongStorage::SongStorage():
    SongHeader()
{
    url.clear();
}

SongStorage::SongStorage(const SongHeader& from)
    :SongStorage::SongStorage()
{
    this->id = from.id;
    this->name = from.name;
    this->size = from.size;
}

SongStorage::SongStorage(const QUrl& from)
    :SongStorage::SongStorage()
{
    if(!from.isValid() || !from.isLocalFile()){
        return;
    }

    this->id = -1;
    if(!getName(name, from)){
        name.clear();
    }

    this->size = QFile(from.toLocalFile()).size();
}

const QUrl& SongStorage::getSource()const{
    return url;
}

bool SongStorage::isValid() const{
    return SongHeader::isValid() && url.isValid();
}

SongStorage::~SongStorage(){
    url.clear();
}

QMediaContent SongStorage::toMedia()const{
    return QMediaContent(url);
}

bool SongStorage::toSong(Song&)const{
    Song song(*((SongHeader*)this));

    QFile f(url.toLocalFile());

    if(!f.open(QIODevice::ReadOnly))
        return false;
    song.source = f.readAll();

    f.close();
    return song.isValid();
}

QDataStream& operator << (QDataStream& stream,const SongStorage& song){
    stream << static_cast<const SongHeader&>(song);
    stream << song.url;
    return stream;
}

QDataStream& operator >> (QDataStream& stream, SongStorage& song){
    stream >> static_cast<SongHeader&>(song);
    stream >> song.url;
    return stream;
}


Song::Song():
    SongHeader()
{
    source.clear();
}

Song::Song(const SongHeader& from)
    :Song::Song()
{
    this->id = from.id;
    this->name = from.name;
    this->size = from.size;
}

void Song::clear(){
    source.clear();
}

const QByteArray& Song::getSource()const{
    return source;
}

bool Song::isValid() const{

    return SongHeader::isValid() && source.size() == size;
}

Song::~Song(){
    source.clear();
}

QDataStream& operator << (QDataStream& stream,const Song& song){
    stream << static_cast<const SongHeader&>(song);
    stream << song.source;
    return stream;
}

QDataStream& operator >> (QDataStream& stream, Song& song){
    stream >> static_cast<SongHeader&>(song);
    stream >> song.source;
    return stream;
}

}
