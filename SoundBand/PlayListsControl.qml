import QtQuick 2.4
import QtQuick.Controls 2.3

Item {
    function addItem(obj){
        model.append(obj);
    }

    function removeItem(obj){
        model.remove(obj);
    }

    function clear(){
        model.clear()
    }

    function init(){
        var playlists = [];
        playlists = syncEngine.allPlayLists();

        for(var i = 0; i < playlists.length; i++){
            var temp = Qt.createComponent("PlayListDelegate.qml");
            if(temp.status === Component.Ready){
                var obj = temp.createObject();
                obj.init(playlists[i]);
                parent.addItem(obj);
            }
        }
    }

    GroupBox {
        id: controlBox
        title: qsTr("Your playlists")
        height: 50
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        Button{
            id:add
            width: parent.width / 3
            text: qsTr("Add")
            anchors.top:parent.top
            anchors.left: parent.left

            onClicked: {

            }

        }

        Button{
            id:edit
            width: parent.width / 3
            text: qsTr("edit")
            anchors.top:parent.top
            anchors.left: add.right

        }

        Button{
            id:remove
            width: parent.width / 3
            text: qsTr("remove")
            anchors.top:parent.top
            anchors.left: edit.right

        }
    }

    ListView {
        id: playLists

        anchors.top: controlBox.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        delegate: PlayListDelegate{
        }

        model: ListModel {
            id: model;

        }
    }

}
