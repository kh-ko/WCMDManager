#ifndef SAMPLEMODEL_H
#define SAMPLEMODEL_H

#include <QObject>
#include <QDebug>

class SampleModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mText READ getText NOTIFY signalEventChangedText)

private:
    QString mText;

public:
    QString getText()
    {
        return mText;
    }

    void setText(QString value)
    {
        if(value == mText)
            return;
        mText = value; emit signalEventChangedText(value);
    }

    explicit SampleModel(QObject *parent = nullptr);

signals:
    void signalEventChangedText(QString value);

public slots:
    Q_INVOKABLE void onCommandTest(QString value)
    {
        qDebug() << "test";

        setText(value);
    }

};

#endif // SAMPLEMODEL_H
