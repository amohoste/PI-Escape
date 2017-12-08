#include "GameUICreator.h"


/**
 * laad de levels in start inclusied, stop exclusief
 */
void load_levels(int start, int stop, MenuModel *m);

GameUICreator::GameUICreator() {}


GameUICreator::~GameUICreator() {

}

EntryBuilder &addMainMenuAnimation(EntryBuilder &entryBuilder) {
    return entryBuilder.addAnimation(new SineAnimation(new MoveAnimation(150, 0)), ACTIVATE, false, 1000l)
            .addAnimation(new ReverseAnimation(new FadeInAnimation()), OTHER_ACTIVATED, false, 1000l)
            .addAnimation(new SineAnimation(new MoveAnimation(-400, 0)), OTHER_ACTIVATED, false, 1000l)
            .addAnimation(
                    new ReverseAnimation(
                            new GlyphIteratingAnimation(
                                    new InOutAnimation(new SineAnimation(new MoveAnimation(0, 5))),
                                    1.5f)), DEFAULT, false, 500l)
            .addAnimation(
                    new GlyphIteratingAnimation(
                            new InOutAnimation(new SineAnimation(new MoveAnimation(0, 10))),
                            1.5f), HOVER, true, 2000l)
            .addAnimation(new RainbowColorAnimation(), HOVER, true, 1000l);
}

void start_game(MenuModel *m) {

    //filmpjes inladen die gespeeld moeten worden na actie
    GameUICreator *gc = new GameUICreator;
    m->getMovieDefinitions()->push_back(gc->createCredits());
    m->getMovieDefinitions()->push_back(gc->createStarWarsCredits());

    load_levels(8, 11, m);
    delete gc;
}

void tutorial(MenuModel *m) {
    m->setActivated(true);
    load_levels(1, 7, m);
    m->fireInvalidationEvent();
}

/**
 * laad de levels in start inclusied, stop exclusief
 */
void load_levels(int start, int stop, MenuModel *m) {
    vector<Level *> *level_names = new vector<Level*>;
    for (int i = stop - 1; i >= start; i--) {
        Level *x = load_level(i);
        level_names->push_back(x);
    }
    m->setLevels(level_names);
}

void endMenu(MenuModel *m) {
    m->setDone(true);
}

std::shared_ptr<MenuDefinition> GameUICreator::createGameMenu() {
    MenuBuilder builder;
    t_vec3 background_color = {0.0f, 0.0f, 0.3f};

    builder.setBackGroundColor(background_color);


    t_vec4 menuEntryColor = {0.0f, 1.0f, 0.0f, 1.0f};

    addMainMenuAnimation(builder.getEntryBuilder())
            .setEnabledOnPc(true).setEnabledOnPi(true)
            .setLongText("Start Tutorial")
            .setShortText("Tut")
            .setMnemonic('T')
            .setFontName("arcade")
            .setFunction(tutorial)
            .setColor(menuEntryColor)
            .buildEntryWithAction("start tutorial");


    addMainMenuAnimation(builder.getEntryBuilder())
            .setEnabledOnPc(true).setEnabledOnPi(true)
            .setLongText("Start Game")
            .setShortText("Go")
            .setMnemonic('G')
            .setFontName("arcade")
            .setFunction(start_game)
            .setColor(menuEntryColor)
            .buildEntryWithAction("start game");

    addMainMenuAnimation(builder.getEntryBuilder())
            .setEnabledOnPc(true).setEnabledOnPi(true)
            .setLongText("Exit")
            .setShortText("Exit")
            .setMnemonic('E')
            .setFontName("arcade")
            .setFunction(endMenu)
            .setColor(menuEntryColor)
            .buildEntryWithAction("quit");

    return std::shared_ptr<MenuDefinition>(builder.build());
}

std::shared_ptr<MovieDefinition> GameUICreator::createIntro() {
    t_vec3 background_color = {0.0f, 0.0f, 0.3f};

    MovieBuilder builder;
    builder.setDuration(10000l)
            .setBackgroundColor(background_color);

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
            .setPos_percent(50.0f, 25.0f)
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
                    new SineAnimation(new FloatInAnimation(0, 400)), 1.0f),
                          0000l, 3000l)
            .addAnimation(
                    new GlyphIteratingAnimation(new FadeInAnimation(), 1.0f), 0000l, 3000l)
            .endText();

    return std::shared_ptr<MovieDefinition>(builder.build());
}

std::shared_ptr<MovieDefinition> GameUICreator::createStarWarsCredits() {
    t_vec4 col1 = {1.0f, 1.0f, 0.0f, 1.0f};
    t_vec3 background = {0.0f, 0.0f, 0.0f};

    MovieBuilder builder;
    builder.setDuration(8000l)
            .setBackgroundColor(background);

    builder.addText("$  @ #")
            .setPos_percent(50.0f, 75.0f)
            .setFont("starwars")
            .setColor(col1)
            .setStartTime(0l)
            .setEndTime(4000l)
            .endText();

    builder.addText("$  @ #")
            .setPos_percent(50.0f, 75.0f)
            .setFont("crossedwars")
            .setColor(col1)
            .setStartTime(4000l)
            .setEndTime(7000l)
            .addAnimation(new SineAnimation(new MoveAnimation(500, 500)), 2000l, 3000l)
            .endText();

    builder.addText("oops...")
            .setPos_percent(50.0f, 50.0f)
            .setFont("starwars")
            .setColor(col1)
            .setStartTime(3000l)
            .setEndTime(7000l)
            .addAnimation(new ReverseAnimation(new FadeInAnimation()), 2500l, 3000l)
            .endText();

    t_vec4 col2 = {0.6f, 0.6f, 0.6f, 1.0f};
    builder.addText("_")
            .setPos_percent(150.0f, 50.0f)
            .setFont("falcon")
            .setColor(col2)
            .setStartTime(0000l)
            .setEndTime(4000l)
            .addAnimation(new SineAnimation(new MoveAnimation(-3000, 100)), 0000l, 3000l)
            .endText();

    return shared_ptr<MovieDefinition>(builder.build());
}

std::shared_ptr<MovieDefinition> GameUICreator::createCredits() {
    t_vec4 col1 = {1.0f, 0.0f, 0.0f, 1.0f};
    t_vec3 background = {0.0f, 0.0f, 0.3f};

    MovieBuilder builder;
    builder.setDuration(12000l)
            .setBackgroundColor(background);

    builder.addText("Pi Escape 2")
            .setPos_percent(50.0f, 80.0f)
            .setFont("atari")
            .setColor(col1)
            .setStartTime(0000l)
            .setEndTime(10000l)
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
                    new SineAnimation(new FloatInAnimation(0, 1000)), 1.0f),
                          0000l, 3000l)
            .endText();

    builder.addText("by")
            .setPos_percent(50.0f, 65.0f)
            .setFont("arcade")
            .setColor(col1)
            .setStartTime(0000l)
            .setEndTime(10000l)
            .addAnimation(
                    new SineAnimation(new FloatInAnimation(1000, 0)),
                    0000l, 3000l)
            .addAnimation(new RepeatAnimation(
                    new RainbowColorAnimation(), 3),
                          0000l, 9000l)

            .addAnimation(new ReverseAnimation(new FadeInAnimation()), 9000l, 1000l)
            .endText();

    builder.addText("Amory Hoste")
            .setPos_percent(50.0f, 55.0f)
            .setFont("arcade")
            .setColor(col1)
            .setStartTime(0000l)
            .setEndTime(10000l)
            .addAnimation(
                    new SineAnimation(new FloatInAnimation(0, 1000)),
                    0000l, 3000l)
            .addAnimation(new ReverseAnimation(new FadeInAnimation()), 9000l, 1000l)
            .endText();

    builder.addText("Arne Goeteyn")
            .setPos_percent(50.0f, 45.0f)
            .setFont("arcade")
            .setColor(col1)
            .setStartTime(0000l)
            .setEndTime(10000l)
            .addAnimation(
                    new SineAnimation(new FloatInAnimation(0, 1000)),
                    0000l, 3000l)
            .addAnimation(new ReverseAnimation(new FadeInAnimation()), 9000l, 1000l)
            .endText();

    builder.addText("Tom Lauwaerts")
            .setPos_percent(50.0f, 35.0f)
            .setFont("arcade")
            .setColor(col1)
            .setStartTime(0000l)
            .setEndTime(10000l)
            .addAnimation(
                    new SineAnimation(new FloatInAnimation(0, 1000)),
                    0000l, 3000l)
            .addAnimation(new ReverseAnimation(new FadeInAnimation()), 9000l, 1000l)
            .endText();

    builder.addText("Jorg Wieme")
            .setPos_percent(50.0f, 25.0f)
            .setFont("arcade")
            .setColor(col1)
            .setStartTime(0000l)
            .setEndTime(10000l)
            .addAnimation(
                    new SineAnimation(new FloatInAnimation(0, 1000)),
                    0000l, 3000l)
            .addAnimation(new ReverseAnimation(new FadeInAnimation()), 9000l, 1000l)
            .endText();

    return shared_ptr<MovieDefinition>(builder.build());
}

std::shared_ptr<MovieDefinition> GameUICreator::createOutro() {
    MovieBuilder builder;

    t_vec3 background = {0.0f, 0.0f, 0.3f};

    builder.setDuration(10000l)
            .setBackgroundColor(background);

    t_vec4 col1 = {1.0f, 1.0f, 0.0f, 1.0f};
    t_vec4 col2 = {0.0f, 1.0f, 1.0f, 1.0f};


    builder.addText("We hope to see you again!")
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
                    new SineAnimation(new FloatInAnimation(0, 400)), 1.0f),
                          0l, 3000l)
            .addAnimation(new GlyphIteratingAnimation(
                    new FadeInAnimation(), 1.0f),
                          0l, 3000l)
            .addAnimation(new ReverseAnimation(new FadeInAnimation()), 9000l, 1000l)
            .endText();

    return shared_ptr<MovieDefinition>(builder.build());
}

