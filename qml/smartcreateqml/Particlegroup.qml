import QtQuick 2.0
import QtQuick.Particles 2.10

Rectangle
{
    id:root
    width: parent.width
    height: parent.height
    color: "black"

    ParticleSystem
    {
        id:particleSystem
    }

    Emitter
    {
        id:emitter
        system: particleSystem
        width: parent.width
        height: 19
        anchors.bottom: root.bottom

        emitRate: 10
        lifeSpan: 6000
        lifeSpanVariation: 3000
        size: 10
        endSize: 30
        group: 'rocket'
        maximumEmitted: 40      //同时存活粒子数

        velocity: AngleDirection
        {
            angle:270
            angleVariation:150
            magnitude:150
            magnitudeVariation:50
        }
        acceleration:AngleDirection
        {
            angle:90
            magnitude:50
        }
    }

    TrailEmitter        //追踪发射器(尾迹)
    {
        id:smokeemitter
        system:particleSystem
        emitHeight:1
        emitWidth:4
        group:'smoke'
        follow:'rocket'         //跟随
        lifeSpan:300
        size:10
        endSize:0
        sizeVariation:6
        emitRatePerParticle:96

        velocity:AngleDirection
        {
            angle:90
            magnitude:100
            magnitudeVariation:20
        }
    }

    Friction        //摩擦减速
    {
        groups: 'rocket'
        width: parent.width
        height: 80
        anchors.top: root.top
        system: particleSystem
        threshold: 5
        factor: 0.9
    }
    Turbulence
    {
        system: particleSystem
        groups: 'rocket'
        width: parent.width
        height: parent.height*0.6
        anchors.centerIn: parent
        strength: 25
    }

    ImageParticle
    {
        id:smokepainter
        system: particleSystem
        groups: ['smoke']
        source: "qrc:/pinwheel.png"
        entryEffect: ImageParticle.None
        alpha: 0.5      //叠加效果
    }
    ImageParticle
    {
        id:rcketpainter
        system: particleSystem
        groups: ['rocket']
        source:  "qrc:/pinwheel.png"
        entryEffect: ImageParticle.None
    }

//爆炸效果

    ImageParticle {
        id: sparklePainter
        system: particleSystem
        groups: ['sparkle']
        color: 'red'
        colorVariation: 0.6
        source: "qrc:/pinwheel.png"
        alpha: 0.3
    }

    ParticleGroup       //粒子组
    {
        name:'explosion'
        system: particleSystem

        TrailEmitter
        {
            id: explosionEmitter
            anchors.fill: parent
            group: 'sparkle'
            follow: 'rocket'
            lifeSpan: 350
            emitRatePerParticle: 200
            size: 32
            velocity: AngleDirection { angle: -90; angleVariation: 180; magnitude: 50 }
        }

        TrailEmitter
        {
            id: explosion2Emitter
            anchors.fill: parent
            group: 'sparkle'
            follow: 'rocket'
            lifeSpan: 750
            emitRatePerParticle: 100
            size: 32
            velocity: AngleDirection { angle: 90; angleVariation: 180; magnitude: 200 }
        }
    }

    GroupGoal       //组控制器
    {
        id:roketchanger
        width:parent.width
        height:230
        anchors.top:root.top
        system:particleSystem
        groups:['rocket']
        goalState:'explosion'
        jump:true       //立即变化

    }

}
