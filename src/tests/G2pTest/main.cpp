#include <QApplication>
#include <QDebug>

#include "g2pglobal.h"
#include "zhg2p.h"
#include <QCoreApplication>
#include <QElapsedTimer>
#include <iostream>
#include <sstream>

#include "JyuptingTest.h"
#include "ManTest.h"

using namespace G2pTest;
int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    IKg2p::setDictionaryPath(qApp->applicationDirPath() + "/dict");

    ManTest manTest;
    qDebug() << "Mandarin G2P test:";
    qDebug() << "--------------------";
    manTest.convertNumTest();
    manTest.removeToneTest();
    manTest.batchTest();
    qDebug() << "--------------------\n";

    JyuptingTest jyuptingTest;
    qDebug() << "Cantonese G2P test:";
    qDebug() << "--------------------";
    jyuptingTest.convertNumTest();
    jyuptingTest.removeToneTest();
    jyuptingTest.batchTest();
    qDebug() << "--------------------\n";

    qDebug() << "G2P mix test:";
    qDebug() << "--------------------";
    auto g2p_zh = new IKg2p::ZhG2p("mandarin");
    QString raw2 =
        "举杯あャ坐ュ饮放あ歌竹林间/清风拂 面悄word然xax asx a xxs拨？Q！动初弦/便推开烦恼与尘喧/便还是当时的少年";
    qDebug() << g2p_zh->convert(raw2, false, false);
    qDebug() << "--------------------";

    return 0;
}