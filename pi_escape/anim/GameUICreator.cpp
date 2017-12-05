#include "GameUICreator.h"


/**
 * laad de levels in start inclusied, stop exclusief
 */
void load_levels(int start, int stop, MenuModel *m) ;

GameUICreator::GameUICreator() {}


GameUICreator::~GameUICreator() {

}

EntryBuilder &addMainMenuAnimation(EntryBuilder &entryBuilder) {
//    return entryBuilder.addAnimation(new SineAnimation(new MoveAnimation(150, 0)), ACTIVATE, false, 1000l)
//            .addAnimation(new ReverseAnimation(new FadeInAnimation()), OTHER_ACTIVATED, false, 1000l)
//            .addAnimation(new SineAnimation(new MoveAnimation(-400, 0)), OTHER_ACTIVATED, false, 1000l)
//            .addAnimation(
//                    new ReverseAnimation(
//                            new GlyphIteratingAnimation(
//                                    new InOutAnimation(new SineAnimation(new MoveAnimation(0, 5))),
//                                    1.5f)), DEFAULT, false, 500l)
//            .addAnimation(
//                    new GlyphIteratingAnimation(
//                            new InOutAnimation(new SineAnimation(new MoveAnimation(0, 10))),
//                            1.5f), HOVER, true, 2000l)
//            .addAnimation(new RainbowColorAnimation(), HOVER, true, 1000l);
    return entryBuilder;
}

void start_game(MenuModel *m) {
    load_levels(8,11,m);
}

void tutorial(MenuModel *m) {
    load_levels(1, 8, m);
}

/**
 * laad de levels in start inclusied, stop exclusief
 */
void load_levels(int start, int stop, MenuModel *m) {
//    vector<Level *> level_names;
//    level_names.clear();
//    for (int i = stop -1 ; i >= start; i--) {
//        Level *x = load_level(i);
//        level_names.push_back(x);
//    }
//    m->playAnimations();
//    m->setLevels(&level_names);
}

void endMenu(MenuModel *m) {
    m->setDone(1);
}

std::shared_ptr<MenuDefinition> GameUICreator::createGameMenu() {
    MenuBuilder builder;

//    addMainMenuAnimation(builder.getEntryBuilder())
//            .setEnabledOnPc(true).setEnabledOnPi(true)
//            .setLongText("Start Tutorial")
//            .setShortText("Tut")
//            .setMnemonic('T')
//            .setFontName("arcade")
//            .setFunction(tutorial)
//            .buildEntryWithAction("start tutorial");
//
//
//    addMainMenuAnimation(builder.getEntryBuilder())
//            .setEnabledOnPc(true).setEnabledOnPi(true)
//            .setLongText("Start Game")
//            .setShortText("Go")
//            .setMnemonic('G')
//            .setFontName("arcade")
//            .setFunction(start_game)
//            .buildEntryWithAction("start game");
//
//    addMainMenuAnimation(builder.getEntryBuilder())
//            .setEnabledOnPc(true).setEnabledOnPi(true)
//            .setLongText("Exit")
//            .setShortText("Exit")
//            .setMnemonic('E')
//            .setFontName("arcade")
//            .setFunction(endMenu)
//            .buildEntryWithAction("quit");

//    return std::shared_ptr<MenuDefinition>(builder.build());
    return nullptr;
}

std::shared_ptr<MovieDefinition> GameUICreator::createIntro() {
    MovieBuilder builder;
    builder.setDuration(10000l);

    t_vec4 col1 = {1.0f, 1.0f, 0.0f, 1.0f};
    t_vec4 col2 = {0.0f, 1.0f, 1.0f, 1.0f};

    builder.addText("Sysprog 2017 presents:")
            .setFont("arcade")
            .setColor(col1)
            .setPos_percent(50.0f, 75.0f)
            .setStartTime(0000l).setEndTime(7000l)
            .addAnimation(new ColorAnimation(1.0f, 0.0f, 0.0f),
                          1000l, 1000l)
            .addAnimation(new GlyphIteratingAnimation(
                    new ColorAnimation(1.0f, 0.0f, 0.0f), 1.7f),
                          1000l, 1000l)
            .addAnimation(new GlyphIteratingAnimation(
                    new MoveAnimation(0, 20), 3.0f),
                          1000l, 2000l)
            .addAnimation(new FadeInAnimation(), 0l, 2000l)
            .endText();

    builder.addText("PiEscape 2")
            .setFont("zorque")
            .setColor(col2)
            .setPos_percent(50.0f, 0.0f)
            .setStartTime(1000l).setEndTime(10000l)

            .addAnimation(new ReverseAnimation(new FadeInAnimation()), 9000l, 1000l)

            .addAnimation(new RepeatAnimation(
                    new GlyphIteratingAnimation(
                            new InOutAnimation(new SineAnimation(new MoveAnimation(0, 40))),
                            1.5f),
                    1, true, true, false
            ), 3000l, 4000l)
            .addAnimation(new RepeatAnimation(
                    new GlyphIteratingAnimation(
                            new RainbowColorAnimation(), 3.0f), 9),
                          0000l, 9000l)
            .addAnimation(new GlyphIteratingAnimation(
                    new SineAnimation(new MoveAnimation(0, 400)), 1.0f),
                          0000l, 3000l)
            .addAnimation(
                    new GlyphIteratingAnimation(new FadeInAnimation(), 1.0f), 0000l, 3000l)
            .endText();

    return std::shared_ptr<MovieDefinition>(builder.build());
}

std::shared_ptr<MovieDefinition> GameUICreator::createCredits() {
    MovieBuilder builder;
    builder.addText("Hallo dit zijn decredits");

    return shared_ptr<MovieDefinition>(builder.build());
}

std::shared_ptr<MovieDefinition> GameUICreator::createOutro() {
    MovieBuilder builder;

    builder.setDuration(10000l);

    t_vec4 col1 = {1.0f, 1.0f, 0.0f, 1.0f};
    t_vec4 col2 = {0.0f, 1.0f, 1.0f, 1.0f};

    builder.addText("You have reached the end!")
            .setFont("arcade")
            .setColor(col1)
            .setPos_percent(50.0f, 75.0f)
            .setStartTime(0000l).setEndTime(7000l)
//            .addAnimation(new ColorAnimation(1.0f, 0.0f, 0.0f),
//                          AnimationType::IN_OUT, 1000l, 1000l)
            .addAnimation(new GlyphIteratingAnimation(
                    new ColorAnimation(1.0f, 0.0f, 0.0f), 1.7f),
                          1000l, 1000l)
            .addAnimation(new GlyphIteratingAnimation(
                    new SineAnimation(new MoveAnimation(0, 20)), 3.0f),
                          1000l, 2000l)
            .addAnimation(new FadeInAnimation(), 0l, 2000l)
            .endText();

    builder.addText("Thank you for playing PiEscape 2.")
            .setFont("zorque")
            .setColor(col2)
            .setPos_percent(50.0f, 25.0f)
            .setStartTime(1000l).setEndTime(10000l)
            .addAnimation(
                    new RepeatAnimation(
                            new GlyphIteratingAnimation(
                                    new RainbowColorAnimation(), 10.5f),
                            9, true, false, true), 0l, 9000l)
            .addAnimation(new GlyphIteratingAnimation(
                    new SineAnimation(new MoveAnimation(0, 400)), 1.0f),
                          0l, 3000l)
            .addAnimation(new GlyphIteratingAnimation(
                    new FadeInAnimation(), 1.0f),
                          0l, 3000l)
            .addAnimation(new ReverseAnimation(new FadeInAnimation()), 9000l, 1000l)
            .endText();

    return shared_ptr<MovieDefinition>(builder.build());
}

