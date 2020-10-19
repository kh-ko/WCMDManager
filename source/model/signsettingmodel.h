#ifndef SIGNSETTINGMODEL_H
#define SIGNSETTINGMODEL_H

#include <QObject>

class SignSettingModel : QObject
{
    Q_OBJECT

    Q_PROPERTY(bool     mIsCheckWrite     READ getIsCheckWrite     NOTIFY signalEventChangedIsCheckWrite    );
    Q_PROPERTY(bool     mIsCheckReview    READ getIsCheckReview    NOTIFY signalEventChangedIsCheckReview   );
    Q_PROPERTY(bool     mIsCheckApproved  READ getIsCheckApproved  NOTIFY signalEventChangedIsCheckApproved );

public:
    bool    mIsCheckWrite       = false;
    bool    mIsCheckReview      = false;
    bool    mIsCheckApproved    = false;

    bool    getIsCheckWrite     (){ return mIsCheckWrite   ;}
    bool    getIsCheckReview    (){ return mIsCheckReview  ;}
    bool    getIsCheckApproved  (){ return mIsCheckApproved;}

    void    setIsCheckWrite     (bool  value){ if(mIsCheckWrite    == value) return; mIsCheckWrite    = value; emit signalEventChangedIsCheckWrite   (mIsCheckWrite   ); }
    void    setIsCheckReview    (bool  value){ if(mIsCheckReview   == value) return; mIsCheckReview   = value; emit signalEventChangedIsCheckReview  (mIsCheckReview  ); }
    void    setIsCheckApproved  (bool  value){ if(mIsCheckApproved == value) return; mIsCheckApproved = value; emit signalEventChangedIsCheckApproved(mIsCheckApproved); }

signals:
    void signalEventChangedIsCheckWrite   (bool value);
    void signalEventChangedIsCheckReview  (bool value);
    void signalEventChangedIsCheckApproved(bool value);

public:
    explicit SignSettingModel(QObject *parent = nullptr):QObject(parent){}
    SignSettingModel(bool isCheckWrite, bool isCheckReview, bool isCheckApproved)
    {
        setIsCheckWrite   (isCheckWrite   );
        setIsCheckReview  (isCheckReview  );
        setIsCheckApproved(isCheckApproved);
    }
    SignSettingModel& operator=(SignSettingModel other)
    {
        setIsCheckWrite   (other.mIsCheckWrite   );
        setIsCheckReview  (other.mIsCheckReview  );
        setIsCheckApproved(other.mIsCheckApproved);
        return *this;
    }
};
#endif // SIGNSETTINGMODEL_H
