#include "languagehelper.h"

#include <QApplication>
#include <QQmlContext>
#include <QQmlEngine>
#include <QDebug>

LanguageHelper * LanguageHelper::mpSelf = nullptr;

LanguageHelper::LanguageHelper(QObject *parent) : QObject(parent)
{
    qDebug() << "Call";

    mpSelf = this;
}

LanguageHelper::~LanguageHelper()
{
    qDebug() << "[LanguageHelper::~LanguageHelper]Call";
}

LanguageHelper* LanguageHelper::getInstance()
{
    return mpSelf;
}

void LanguageHelper::setContext(QObject * context)
{
    qDebug() << "[LanguageHelper::setContext]";
    mContext = context;
}

void LanguageHelper::loadLanguage(EnumDefine::Language value)
{
    if(qApp == nullptr || mContext == nullptr || QQmlEngine::contextForObject(mContext) == nullptr || QQmlEngine::contextForObject(mContext)->engine() == nullptr)
    {
        qDebug() << "[LanguageHelper::loadLanguage]not loaded pApp";
        return;
    }

    qDebug() << mLanguage << " to " << value;
    if(mLanguage == value)
    {
        qDebug() << "same language";
        return;
    }

    do
    {
        if(value == EnumDefine::Language::LANG_ENG)
        {
            if(qApp->removeTranslator(&(mTranslator)) == false)
            {
                break;
            }

        }
        else if(value == EnumDefine::Language::LANG_KOR)
        {
            if(mTranslator.load(":/Lang_ko_KR"))
            {
                qDebug() << "load : Lang_ko_KR";
                qApp->installTranslator(&(mTranslator));
                qDebug() << "load : end";
            }
            else
            {
                break;
            }
        }

        mLanguage = value;

        QQmlEngine::contextForObject(mContext)->engine()->retranslate();

        return;
    }while(0);

    qDebug() << "changed failed";
}
