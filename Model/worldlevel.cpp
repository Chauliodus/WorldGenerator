#include "Model/worldlevel.h"

#include "world.h"

// Примечание: ландмарки - примечательные объекты: здания, люди и группы, поселения, животные, странные штуки, ресурсы и пр.

WorldLevel::WorldLevel(World *parent) : world_parent(parent)
// Определяет ЛАНДШАФТ уровня (горы, лес, болото...)
{
    landscape = static_cast<Landscapes>(rand()%3 + reinterpret_cast<World *>(parent)->fraction * 3); // цвет * высоту над морем
    if ((landscape == Landscapes::MATRIX_1) || (landscape == Landscapes::MATRIX_11))
        landscape = Landscapes::MATRIX;
    size = rand()%26 + 7; // число ландмарок на уровне
    generateLandmarks();
    generatePicture();
    generateDescription();
}

WorldLevel::~WorldLevel()
{
    for(int i = 0; i < size; i++){
        delete landmark_list[i];
    }
}

QPixmap WorldLevel::generatePicture() // Уже готовые фоновые изображения. На них будут наложены превьюхи ландмарков,
                                      // при отрисовке уровня
{
    switch (landscape) {
        case Landscapes::CAVES : picture.load("../res/landscapes/caves.png"); break;
        case Landscapes::PEAKS : picture.load("../res/landscapes/peaks.png"); break;
        case Landscapes::PLATEAU : picture.load("../res/landscapes/plateau.png"); break;
        case Landscapes::HIGHLAND : picture.load("../res/landscapes/highland.png"); break;
        case Landscapes::PLAIN : picture.load("../res/landscapes/plain.png"); break;
        case Landscapes::LOWLAND : picture.load("../res/landscapes/lowland.png"); break;
        case Landscapes::MATRIX : picture.load("../res/landscapes/matrix.png"); break;
        case Landscapes::MATRIX_1 : picture.load("../res/landscapes/matrix.png"); break;
        case Landscapes::MATRIX_11 : picture.load("../res/landscapes/matrix.png"); break;
        case Landscapes::ICE_WASTELAND : picture.load("../res/landscapes/ice_wasteland.png"); break;
        case Landscapes::GLACIES : picture.load("../res/landscapes/glacies.png"); break;
        case Landscapes::MECH_FOREST : picture.load("../res/landscapes/mech_forest.png"); break;
        case Landscapes::LIGHT : picture.load("../res/landscapes/light.png"); break;
        case Landscapes::SOUND : picture.load("../res/landscapes/sound.png"); break;
        case Landscapes::VIBRO : picture.load("../res/landscapes/vibro.png"); break;
        case Landscapes::OPEN_COSMO : picture.load("../res/landscapes/open_cosmo.png"); break;
        case Landscapes::STAR_CLUSTER : picture.load("../res/landscapes/star_cluster.png"); break;
        case Landscapes::BLACK_HOLE_ORBIT : picture.load("../res/landscapes/black_hole_orbit.png"); break;
    }
    return picture;
}

QString WorldLevel::generateDescription()
{
    description = "На этом уровне вас окружает ";
    switch (landscape) {
        case Landscapes::CAVES : description += "пещеры, в которых неосторожному путнику легко заблудиться."; break;
        case Landscapes::PEAKS : description += "кристаллические скалы, острые и тонкие, но хрупкие."; break;
        case Landscapes::PLATEAU : description += "пустынное плато, на котором практически не встречаются полезные "
                                                  "ископаемые. В изобилии тут только колючки."; break;
        case Landscapes::HIGHLAND : description += "горные вершины."; break;
        case Landscapes::PLAIN : description += "зеленая долина."; break;
        case Landscapes::LOWLAND : description += "низина с затхлым воздухом."; break;
        case Landscapes::MATRIX : description += "числовая матрица."; break;
        case Landscapes::MATRIX_1 : description += "числовая матрица."; break;
        case Landscapes::MATRIX_11 : description += "числовая матрица."; break;
        case Landscapes::ICE_WASTELAND : description += "ледяная пустыня."; break;
        case Landscapes::GLACIES : description += "ледник."; break;
        case Landscapes::MECH_FOREST : description += "механический лес."; break;
        case Landscapes::LIGHT : description += "свет."; break;
        case Landscapes::SOUND : description += "звук."; break;
        case Landscapes::VIBRO : description += "вибрация."; break;
        case Landscapes::OPEN_COSMO : description += "открытый космос."; break;
        case Landscapes::STAR_CLUSTER : description += "звездное скопление."; break;
        case Landscapes::BLACK_HOLE_ORBIT : description += "орбита черной дыры."; break;
    }
    return description;
}

void WorldLevel::generateLandmarks() // вычисляются вероятности попадения какой-либо ландмарки на этот уровень.
// вероятность генерации того или иного объекта зависит от:
// (кроме людей, животных, трав и просто ресурсов):
// - цветозависимые ландмарки - появляются только в мирах определенного цвета
// - ландшафтозависимые - появляются только на опред. ландш. или высотах
// - природозависимые - только при низкой/высокой колич. оценке природы
// - разумозависимые - как и предыдущее, только с разумной жизнью
// - агрессозависимые - как и предыдущие, только с агрессией
// - ничего-не-найдено - 10 - вероятность найти "абсолютно ничего" всегда одинакова, но я еще подумаю
// - водоемы
//
{
    int a;
    for(int i = 0; i < size; i++){ // создаем ландмарки разных типов.
        a = rand()%9;// Объект создается, только если к тому нет противопоказаний, таких как полное отсуствие живности в мире, например.
        switch (a){// иначе вместо создания ландмарки счетчик сбрасывается на единицу.
            case 0: {
                Item * item = new Item(this);
                item->parent = nullptr;
                landmark_list.push_back(item);
                connect(landmark_list.last(), &Item::sigItemAddingToInventory, world_parent, &World::catchedItemCreatedSig);
                break;
            }
            case 1: {
                if (world_parent->urbanisation > 0) {
                    landmark_list.push_back(new Unit(this));
                    connect(landmark_list.last(), &Unit::sigUnitMet, world_parent, &World::catchedUnitMetSig);
                } else {
                    i--;
                }
                break;
            }
            case 2: {
                if (world_parent->urbanisation > 0) {
                    landmark_list.push_back(new Building(this));
                } else {
                    i--;
                }
                break;
            }
            case 3: {
                landmark_list.push_back(new Realty(this));
                connect(landmark_list.last(), &Realty::sigItemAddingToInventory, world_parent, &World::catchedItemCreatedSig);
                break;
            }
            case 4: {
                if(world_parent->agressy > 0 && number > 0) {
                    landmark_list.push_back(new Mischance(this));
                } else {
                    i--;
                }
                break;
            }
            case 5: {
               if(world_parent->nature > 1 || world_parent->urbanisation > 1) {
                    landmark_list.push_back(new Manmade(this));
               } else {
                   i--;
               }
                break;
            }
            case 6: {
                landmark_list.push_back(new Water(this));
                break;
               }
           case 7: {
               if(world_parent->nature > 0 || world_parent->urbanisation > 0) {
                    landmark_list.push_back(new Trail(this));
               } else {
                   i--;
               }
               break;
            }
            case 8: {
                if(world_parent->urbanisation > 0) {
                     landmark_list.push_back(new Settlement(this));
                } else {
                    i--;
                }
                break;
             }
        }
    }

    for(int i = 0; i < size; i++){ // для порядка лучше раскидать на два цикла
        landmark_list[i]->number = i; // ландмарке присваивается порядковый номер. Позже может пойти в curloc game'а
        connect(landmark_list[i], &Landmark::sigIsItemInStack, world_parent,  &World::catchedIsInStockSig);
        if (landscape == Landscapes::CAVES ||    // Если ландшафт из этого списка, то ландмарки могут быть где угодно.
                landscape == Landscapes::LIGHT ||
                landscape == Landscapes::SOUND ||
                landscape == Landscapes::VIBRO ||
                landscape == Landscapes::MATRIX ||
                landscape == Landscapes::OPEN_COSMO ||
                landscape == Landscapes::STAR_CLUSTER ||
                landscape == Landscapes::BLACK_HOLE_ORBIT) {   // их координаты будут в таких пределах
            landmark_list[i]->x = rand()%546; // размер поля по ИКС - 730, размер картинки - 184, 546 - самая правая координата
            landmark_list[i]->y = rand()%243; //      по ИГРЕК - 380,                 - 137, 243 - самая нижняя координата
        }
        if (landscape == Landscapes::PEAKS ||
                landscape == Landscapes::GLACIES ||       // Пики, ледник и высокогорье - ландмарки где угодно по ИКС
                landscape == Landscapes::HIGHLAND){         // и в нижних трех четвертях по ИГРЕК
            landmark_list[i]->x = rand()%546;
            while(landmark_list[i]->y < 163 || landmark_list[i]->y > 243)
                landmark_list[i]->y = rand()%120 + 83;
        }
        if (landscape == Landscapes::PLAIN || landscape == Landscapes::PLATEAU || landscape == Landscapes::MECH_FOREST){
            landmark_list[i]->x = rand()%546;
            while(landmark_list[i]->y < 123 || landmark_list[i]->y > 243)
                landmark_list[i]->y = rand()%160 + 123; // Равнины, плато, мех.лес - равнинного типа
        }
        if (landscape == Landscapes::LOWLAND || landscape == Landscapes::ICE_WASTELAND){
            landmark_list[i]->x = rand()%546;
            while(landmark_list[i]->y < 163 || landmark_list[i]->y > 243)
                landmark_list[i]->y = rand()%200 + 163;     // низина и лед.пустоши - низины
        }
    }
}
