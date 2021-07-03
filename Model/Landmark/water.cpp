#include "water.h"
#include "Model/worldlevel.h"
#include "Model/world.h"

Water::Water(WorldLevel * parent) : Landmark(parent)
{
    type = LndmType::WATER;
    loadPicture();
    generateName();
    generateDescription();
    isSeenFromAfar = 0;
    isCanBeAddedOnMap = 1;
    isAddedOnMap = 0;
    get_string = "Набрать воды";
    /*
    $landmark['название'] = 'водоем'

    volume = RAND(1,4)

    if volume = 1 :
        $landmark['тип'] = 'родник'
        $landmark['охват уровней'] = '1'
    end
    if volume = 2 :
        $landmark['тип'] = 'пруд'
        $landmark['охват уровней'] = '1'
    end
    if volume = 3 :
        $landmark['тип'] = 'озеро'
        $landmark['охват уровней'] = str(rand(1,5 - world_level))
    end
    if volume = 4 :
        $landmark['тип'] = 'река'
        $landmark['охват уровней'] = str(rand(1,5 - world_level))
    end

    if $color = 'красный' :
        if rand(0,1) = 1 :
            $landmark['ресурс'] = 'горючее'
            else :
                $landmark['ресурс'] = 'ртуть'
            end
        end
    end
    if $color = 'зеленый' : $landmark['ресурс'] = 'вода' &! спирт? растворитель?
    if $color = 'синий' : $landmark['ресурс'] = 'электроны'
    if $color = 'циан' :
        if rand(0,1) = 1 :
            $landmark['ресурс'] = 'антифриз'
            else :
                $landmark['ресурс'] = 'охладитель'
            end
        end
    end
    if $color = 'желтый' : $landmark['ресурс'] = 'волны восприятия'
    if $color = 'фиолетовый' : $landmark['ресурс'] = 'эктоплазма'

    $landmark['описание'] = 'Перед вами открывается живописный <<$landmark[''название'']>> - <<$landmark[''тип'']>>. В его берегах течет <<$landmark[''ресурс'']>>.<br>'

    if VAL($landmark['охват уровней']) > 1 : $landmark['описание'] = $landmark['описание'] + 'Это достаточно большой водоем. Если построить соответствующий корабль, можно передвигаться по миру значительно быстрее.<br>'

    if $landmark['тип'] = 'река' :
        v = rand(1,5)
        if v = 1 : $landmark['скорость течения'] = 'медленная'
        if v = 2 : $landmark['скорость течения'] = 'небыстрая'
        if v = 3 : $landmark['скорость течения'] = 'умеренная'
        if v = 4 : $landmark['скорость течения'] = 'быстрая'
        if v = 5 : $landmark['скорость течения'] = 'бурная'
        if rand(0,1) = 1 : $landmark['направление'] = 'вглубь мира' else : $landmark['направление'] = 'к генератору'
        $landmark['описание'] = $landmark['описание'] + 'Река отличается от озера наличием течения. Против течения движение замедлится, а по течению можно отправлять баржи или сплавлять плавучие ресурсы. Однако быстрое течение опасно мелями и водоворотами. Без навигации соваться в такую реку может быть рискованно.

    Это <<$landmark[''скорость течения'']>> река. Она течет <<$landmark[''направление'']>>.<br>'
    end

                           */
}
void Water::generateName()
{
    int a = rand()%4;
    switch (a) {
        case 0 : name = "Река"; break;
        case 1 : name = "Озеро"; break;
        case 2 : name = "Пруд"; break;
        case 3 : name = "Родник"; break;
    }
}
void Water::generateDescription()
{
    description = "Водоем с неведомой жидкостью";
}

void Water::loadPicture()
{
    picture.load("../res/water/river.png");
    picture_preview.load("../res/water/river_preview.png");
    picture_preview_hovered.load("../res/water/river_preview_hovered.png");
}
void Water::research()
{
    qDebug() << name << " " << description;

}
void Water::get()
{
    qDebug() << "Get" << name << " " << description;
}

void Water::onVisit()
{
    actions.clear();
    actions.push_back(new QPair<QString, QString>("Осмотреть", "research"));
    actions.push_back(new QPair<QString, QString>("Наблюдать", "research"));
    actions.push_back(new QPair<QString, QString>("Набрать воды", "get"));
    actions.push_back(new QPair<QString, QString>("Искупаться", "research"));
    actions.push_back(new QPair<QString, QString>("Ловить рыбу", "research"));
}
void Water::destroy()
{

}
