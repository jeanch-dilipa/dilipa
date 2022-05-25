import QtQuick 2.0
import QtQuick.Window 2.3
import QtQuick.Particles 2.12

Window
{
    id:root
    width: 1024
    height: 768
    flags: Qt.FramelessWindowHint
    opacity: 0.9
    color: "#a8a8a8a8"

    /*粒子系统*/
    ParticleSystem
    {
        id:particlesystem
    }

    /*发射器*/
    Emitter
    {
        id:emitter
        anchors.centerIn: parent
        anchors.fill: parent
        system: particlesystem
        emitRate: 30
        lifeSpan: 10000
        lifeSpanVariation: 6000
        size: 2
        sizeVariation: 10
        endSize: 50
        velocity: AngleDirection/*粒子方向控制*/
        {
            angle: 0
            angleVariation: 360
            magnitude: 60  /*加速度*/
            magnitudeVariation: 50
        }
    }

    /*粒子*/
    ImageParticle
    {
        source: "qrc:/new/prefix1/image/bubble.png"
        system: particlesystem
        color: "#0acf97"
        colorVariation: 0.8
        rotation: 0
        rotationVariation: 180
        rotationVelocity: 15
        rotationVelocityVariation: 15
        entryEffect: ImageParticle.Scale
        Attractor/*吸引*/
        {
            id:attractor
            width: root.width
            height: root.height
            system: particlesystem
        }
    }

    MouseArea
    {
        anchors.fill: parent
        onDoubleClicked:
        {
            root.destroy()
        }
        onPressed:
        {
            attractor.pointX = mouseX
            attractor.pointY = mouseY
            attractor.strength = 0.1
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/
