#ifndef NODE_H
#define NODE_H
#include <QTcpServer>
#include "ETcpSocket.h"
#include "song.h"

namespace syncLib {

typedef unsigned char Type;

/**
 * @brief The TypePackage enum
 * t_void - this package empty and not valid.
 * t_close - the information about close channel.
 * t_sync - the infomation about sync playning media file on network.
 * t_song - the package with this type is necessary for translite media data on network.
 * t_stop - the package with type 'stop' necessary for stoping playning media files.
 */
enum TypePackage{
     t_void         =   0x00,
     t_play         =   0x01,
     t_song_h       =   0x02,
     t_song         =   0x04,
     t_sync         =   0x08,
     t_close        =   0x10,
     t_stop         =   0x20,
     t_what         =   0x40,
     t_brodcaster   =   0x80
};

/**
 * @brief The package class. Package for translite media data on network
 *
 * parse map:
 * 1 byle - type
 * 4 byte - size of data of package (it avelable if type is t_sync or t_song)
 * data
 */
class package
{
    /*parse map */

/*
 * 1 byle - type
 * 4 byte - size of data of package (it avelable if type is t_sync or t_song)
 * data
*/

private:
    Type type;
    Song source;
    SongHeader header;
    Syncer playdata;
public:
    package();
    package(QByteArray &array);
    ~package();
    /**
     * @brief getHeader
     * @return Header of the song
     */
    const SongHeader& getHeader() const;
    /**
     * @brief getSong
     * @return Song
     */
    const Song& getSong() const;
    /**
     * @brief getPlayTime
     * @return time of playning media data
     */
    const Syncer &getPlayData() const;
    const Type& getType() const;
    bool isValid() const;
    void clear();
    QByteArray parseTo();
    bool parseFrom(QByteArray& array);
    friend class Sync;
};

class Node:public QTcpServer{
    Q_OBJECT
protected:
    QList<ETcpSocket*> clients;
private slots:
    void acceptError_(ETcpSocket*);
    void newConnection_();
    void readData(ETcpSocket*_client);
public:
    Node();
    void WriteAll(const QByteArray&);
    void disconnectClient(ETcpSocket*);
    QList<ETcpSocket*>* getClients();
    bool addNode(const QString &node, int port = DEDAULT_PORT);
    bool addNode(ETcpSocket* node);
    ~Node();
signals:
    void Error(QString);
    void Message(ETcpSocket*);
    void ClientDisconnected(ETcpSocket*);
    void ClientConnected(ETcpSocket*);
};

}


#endif // NODE_H
