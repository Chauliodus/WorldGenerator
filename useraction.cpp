#include "useraction.h"
#include "view.h"

UserAction::UserAction(QString bname, QString fname, Game * game) : game(game), buttonName(bname), functionName(fname)
{
    view = nullptr;
    landmark = nullptr;
}

UserAction::UserAction(QString bname, QString fname, View * view) : view(view), buttonName(bname), functionName(fname)
{
    game = nullptr;
    landmark = nullptr;
}

UserAction::UserAction(QString bname, QString fname, Landmark * landmark) : landmark(landmark), buttonName(bname), functionName(fname)
{
    game = nullptr;
    view = nullptr;
    isOnMap = landmark->isAddedOnMap && !landmark->isCanBeAddedOnMap;
}

void UserAction::slotAction()
{
    if (game != nullptr) QMetaObject::invokeMethod(game, functionName.toStdString().c_str(), Qt::DirectConnection);
    if (view != nullptr) QMetaObject::invokeMethod(view, functionName.toStdString().c_str(), Qt::DirectConnection);
    if (landmark != nullptr) {
        switch(landmark->type){
            case LndmType::ITEM : {
                landmark = reinterpret_cast<Item *>(landmark);
                break;
            }
            case LndmType::UNIT : {
                landmark = reinterpret_cast<Unit *>(landmark);
                break;
            }
            case LndmType::TRAIL : {
                landmark = reinterpret_cast<Trail *>(landmark);
                break;
            }
            case LndmType::WATER : {
                landmark = reinterpret_cast<Water *>(landmark);
                break;
            }
            case LndmType::REALTY : {
                landmark = reinterpret_cast<Realty *>(landmark);
                break;
            }
            case LndmType::MANMADE : {
                landmark = reinterpret_cast<Manmade *>(landmark);
                break;
            }
            case LndmType::BUILDING : {
                landmark = reinterpret_cast<Building *>(landmark);
                break;
            }
            case LndmType::MISCHANCE : {
                landmark = reinterpret_cast<Mischance *>(landmark);
                break;
            }
            case LndmType::SETTLEMENT : {
                landmark = reinterpret_cast<Settlement *>(landmark);
                break;
            }
        }
        QMetaObject::invokeMethod(landmark, functionName.toStdString().c_str(), Qt::DirectConnection);
    }
}
