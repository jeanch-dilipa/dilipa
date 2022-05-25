import QtQuick 2.0
import QtQuick.Particles 2.0

Rectangle
{
    id: root
    width: parent.width;
    height: parent.height
    color: "black"

    property var realx:100
    property var realy:200

    ParticleSystem      //粒子系统
    {
        id: particleSystem
    }

//    Age     //当生命周期进入lifeleft后开始按照Age老化
//    {
//        anchors.horizontalCenter: root.horizontalCenter
//        width: parent.width/3; height: parent.height/3
//        system: particleSystem
//        advancePosition: true
//        lifeLeft: 3000
//        once: true
//    }

    Attractor       //吸引
    {
//        x:parent.realx-50
//        y:parent.realy-50
//        width: 100; height:100
        width: parent.width; height: parent.height
        system: particleSystem
        pointX: parent.realx        //吸引点
        pointY: parent.realy
        strength: 1.0           //力度
//        affectedParameter :Attractor.Position       //受影响属性
    }
    MouseArea
    {
        anchors.fill: parent
        onMouseXChanged: parent.realx=mouseX
        onMouseYChanged: parent.realy=mouseY
    }

//    Wander      //漂移
//    {
//        width: parent.width; height: parent.height
//        system: particleSystem
////        affectedParameter: Wander.Position          //受影响属性
//        pace: 200               //改变最大值
//        yVariance: 240          //y组件影响
//    }

//    Turbulence      //紊流
//    {
//        anchors.horizontalCenter: parent.horizontalCenter
//        width: 240; height: 120
//        system: particleSystem
//        strength: 100       //影响大小
////        noiseSource:""  //噪声图像
//    }

//    Gravity         //重力（额外加速度）
//    {
//        width: parent.width; height: parent.height/2
//        system: particleSystem
//        magnitude: 50
//        angle: 90
//    }

//    Friction                //摩擦
//    {
//        width: 100; height: parent.height
//        system: particleSystem
//        factor : 0.8        //减慢力度
//        threshold: 25           //阈值
//    }

    Emitter             //粒子发射器
    {
        id: emitter
//        anchors.centerIn: parent
        width: 1//parent.width        //发射范围不等于渲染范围
        height: 1//parent.height
        anchors.verticalCenter:root.verticalCenter
        anchors.left:root.left


        system: particleSystem
        emitRate: 20        //每秒发射粒子数
        lifeSpan: 7000          //粒子生命周期
        lifeSpanVariation: 500      //生命变化周期（关联于size/endsize）
        size: 25
        endSize: 30

        velocity:AngleDirection     //角度方向
        {
            angle:-45
            angleVariation:10
            magnitude: 100
            magnitudeVariation: 25
        }
        acceleration:AngleDirection
        {
            angle:90
            magnitude:25
//            angleVariation:20
//            magnitudeVariation: 50
        }
//        velocity:PointDirection     //点方向
//        {
//            x:200       //x、y方向速度
//            y:50
//            xVariation:200      //角度
//            yVariation:30
//        }
//        velocity:TargetDirection        //目标方向
//        {
//            targetX: 100            //目标点
//            targetY: 50
//            targetVariation: 100/6      //扩散范围
//            magnitude: 100              //加速度
//        }
    }

//    ImageParticle           //图像粒子   可视化_粒子参数
//    {
//        source: "qrc:/pinwheel.png"
//        system: particleSystem
//        color:"#ffd700"
//        colorVariation:0.5      //颜色变化范围
//        rotation:450
//        rotationVariation:200    //变化范围
//        rotationVelocity:200         //旋转速度
//        rotationVelocityVariation:200
//        entryEffect:ImageParticle.Scale     //入场效果
//    }

    ItemParticle            //代理粒子
    {
        id:item
        system:particleSystem
        delegate:itemdelege
        Component
        {
            id:itemdelege
            Rectangle
            {
                width:Math.random()*50
                height: Math.random()*50
                radius: Math.random()*50
                border.width: 5
                border.color: Qt.rgba(Math.random(),Math.random(),Math.random())
            }
        }
    }


//    CustomParticle        //自定义粒子
//    {

//    }
}

