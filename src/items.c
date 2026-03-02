#include <stdio.h>
#include <string.h>

#include "items.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-field-initializers"

item_t initialItems[BOOK_END] = {
    {
        EMPTY, { },
    },
    {
        CREST_KEY,
        {
            ALL_TOWER_1,
            ITEMS_CATHEDRAL_1,
            ITEMS_CATHEDRAL_2,
            ITEMS_LAKMIRS_TOWER_1,
            BOOKS_LAKMIRS_TOWER_1,
            // ITEMS_LAKMIRS_TOWER_2,
            ITEMS_LAKMIRS_TOWER_3,
            BOOKS_LAKMIRS_TOWER_3,
        },
    },
    {
        BOTTLE_OF_OIL,
        {
            ALL_TOWER_1,
            ITEMS_CATHEDRAL_1,
            ITEMS_CATHEDRAL_2,
            ITEMS_LAKMIRS_TOWER_1,
            BOOKS_LAKMIRS_TOWER_1,
        },
    },
    {
        FRAGMENTS_OF_A_CREST,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ALL_VILLAGE,
            ITEMS_TRIALS_1,
            BOOKS_TRIALS_1,
        },
    },
    {
        DRAGON_TEARS,
        {
            ALL_TOWER_1,
            ITEMS_CATHEDRAL_1,
            ITEMS_CATHEDRAL_2,
            ITEMS_LAKMIRS_TOWER_1,
            BOOKS_LAKMIRS_TOWER_1,
            // ITEMS_LAKMIRS_TOWER_2,
        },
    },
    {
        PIXIE_FLUTE,
        {
            ALL_TOWER_1,
        },
    },
    {
        TREASURE,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ITEMS_CATHEDRAL_3,
            BOOKS_CATHEDRAL_3,
            ITEMS_DISCIPLES_TOWER_3,
            ITEMS_VILLAGE_1,
            BOOKS_VILLAGE_1,
            ITEMS_MERCHANT,
            ITEMS_VILLAGE_2,
            ITEMS_VILLAGE_3,
            BOOKS_VILLAGE_3,
            ITEMS_DISCIPLES_TOWER_4,
        },
    },
    {
        RUSTY_KEY,
        {
            // Leaving the first tower without the Rusty Key would lead to a soft-lock.
            // ALL_TOWER_1,
            ALL_TOWER_2,
            ITEMS_CATHEDRAL_3,
            BOOKS_CATHEDRAL_3,
        },
    },
    {
        ORNATE_KEY,
        {
            EVERYTHING,
        },
    },
    {
        RING_OF_THE_KINGDOM,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ALL_VILLAGE,
            ALL_TOWER_3,
        },
    },
    {
        ORB,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ITEMS_CATHEDRAL_3,
            BOOKS_CATHEDRAL_3,
            ITEMS_DISCIPLES_TOWER_3,
            ITEMS_VILLAGE_1,
            BOOKS_VILLAGE_1,
            ITEMS_MERCHANT,
            ITEMS_VILLAGE_2,
            ITEMS_VILLAGE_3,
            BOOKS_VILLAGE_3,
            ITEMS_DISCIPLES_TOWER_4,
        },
    },
    {
        GOLDEN_KEY,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ITEMS_VILLAGE_1,
            BOOKS_VILLAGE_1,
            ITEMS_MERCHANT,
            ITEMS_VILLAGE_2,
            ITEMS_DISCIPLES_TOWER_4,
            ITEMS_VILLAGE_4,
        },
    },
    {
        LIQUID_SUNSET,
        {
            ALL_TOWER_1,
            ITEMS_CATHEDRAL_1,
            ITEMS_CATHEDRAL_2,
            ITEMS_LAKMIRS_TOWER_1,
            BOOKS_LAKMIRS_TOWER_1,
            // ITEMS_LAKMIRS_TOWER_2,
            ITEMS_LAKMIRS_TOWER_3,
            BOOKS_LAKMIRS_TOWER_3,
        },
    },
    {
        NIGHT_ELIXIR,
        {
            ALL_TOWER_1,
            ITEMS_CATHEDRAL_1,
            ITEMS_CATHEDRAL_2,
            ITEMS_LAKMIRS_TOWER_1,
            BOOKS_LAKMIRS_TOWER_1,
            // ITEMS_LAKMIRS_TOWER_2,
            ITEMS_LAKMIRS_TOWER_3,
            BOOKS_LAKMIRS_TOWER_3,
        },
    },
    {
        FOREST_NECTAR,
        {
            EVERYTHING,
        },
    },
    {
        PRIMITIVE_MAN_STATUE,
        {
            EVERYTHING,
        },
    },
    {
        APEMAN_SCULPTURE,
        {
            EVERYTHING,
        },
    },
    {
        FAIRY_SCULPTURE,
        {
            ITEMS_DUNGEON,
            ITEMS_SEWERS_1,
            ITEMS_SEWERS_2,
            BOOKS_SEWERS_2,
            ITEMS_DISCIPLES_TOWER_1,
            BOOKS_DISCIPLES_TOWER_1,
        },
    },
    {
        ELF_STATUE,
        {
            ITEMS_DUNGEON,
            ITEMS_SEWERS_1,
            ITEMS_SEWERS_2,
            BOOKS_SEWERS_2,
            ITEMS_DISCIPLES_TOWER_1,
            BOOKS_DISCIPLES_TOWER_1,
        },
    },
    {
        ANCIENT_COIN,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ITEMS_CATHEDRAL_3,
            BOOKS_CATHEDRAL_3,
            ITEMS_DISCIPLES_TOWER_3,
            ITEMS_VILLAGE_1,
            BOOKS_VILLAGE_1,
            ITEMS_MERCHANT,
            ITEMS_VILLAGE_3,
            BOOKS_VILLAGE_3,
            ITEMS_DISCIPLES_TOWER_4,
        },
    },
    {
        PICKAX,
        {
            ITEMS_DUNGEON,
            ITEMS_SEWERS_1,
            ITEMS_SEWERS_2,
            BOOKS_SEWERS_2,
        },
    },
    {
        RING_OF_THE_DEAD,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
        },
    },
    {
        BLUE_RING,
        {
            EVERYTHING,
        },
    },
    {
        GREEN_RING,
        {
            EVERYTHING,
        },
    },
    {
        LEVER,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ALL_VILLAGE,
        },
    },
    {
        SLIPPER,
        {
            // Slipper pick-ups have specific logic for combining the Pair.
            SLIPPER,
        },
    },
    {
        DIRTY_SLIPPER,
        {
            // Slipper pick-ups have specific logic for combining the Pair.
            DIRTY_SLIPPER,
        },
    },
    {
        PAIR_OF_SLIPPERS,
        {
            // Slippers should always combine to the Pair.
            PAIR_OF_SLIPPERS,
        },
    },
    {
        JEZIBELS_PENDANT,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ITEMS_DISCIPLES_TOWER_3,
            ITEMS_VILLAGE_1,
            BOOKS_VILLAGE_1,
            ITEMS_MERCHANT,
            ITEMS_VILLAGE_2,
            ITEMS_DISCIPLES_TOWER_4,
            ITEMS_CATHEDRAL_3,
        },
    },
    {
        STAFF_OF_AGES,
        {
            // Game will hang on Belzar cutscene if you already have the Staff of Ages.
            // Dwarf Guards going into search early can cause many naviation soft-locks.
            STAFF_OF_AGES,
        },
    },
    {
        ROPE,
        {
            ALL_TOWER_1,
        },
    },
    {
        CEMETERY_KEY,
        {
            EVERYTHING,
        },
    },
    {
        FLOWER,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ITEMS_CATHEDRAL_3,
            BOOKS_CATHEDRAL_3,
            ITEMS_DISCIPLES_TOWER_3,
            ITEMS_VILLAGE_1,
            BOOKS_VILLAGE_1,
            ITEMS_MERCHANT,
            ITEMS_VILLAGE_2,
            ITEMS_VILLAGE_3,
        },
    },
    {
        FLINT,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ALL_VILLAGE,
            ITEMS_TRIALS_1,
            BOOKS_TRIALS_1,
        },
    },
    {
        FANG,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ALL_VILLAGE,
            ALL_TOWER_3,
            ITEMS_DISCIPLES_TOWER_5,
            ITEMS_DRAGON_TOWER_1,
            BOOKS_DRAGON_TOWER_1,
            BOOKS_DRAGON_TOWER_2,
        },
    },
    {
        DRAGON_EYE,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ALL_VILLAGE,
            ALL_TOWER_3,
            ALL_TOWER_4,
        },
    },
    {
        DRAGON_FLUTE,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ALL_VILLAGE,
            ALL_TOWER_3,
            ITEMS_DISCIPLES_TOWER_5,
        },
    },
    {
        BURNING_CANDLE,
        {
            BURNING_CANDLE,
        },
    },
    {
        CHIPPED_VIOLIN,
        {
            // Violins can't be distinguished by icon.
            CHIPPED_VIOLIN,
        },
    },
    {
        VIOLIN_WITHOUT_STRINGS,
        {
            // Violins can't be distinguished by icon.
            VIOLIN_WITHOUT_STRINGS,
        },
    },
    {
        BROKEN_VIOLIN,
        {
            // Violins can't be distinguished by icon.
            BROKEN_VIOLIN,
        },
    },
    {
        DUNGEON_KEY,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ITEMS_CATHEDRAL_3,
            BOOKS_CATHEDRAL_3,
            ITEMS_DISCIPLES_TOWER_3,
            ITEMS_VILLAGE_1,
            BOOKS_VILLAGE_1,
            ITEMS_MERCHANT,
            ITEMS_VILLAGE_2,
            ITEMS_VILLAGE_3,
            BOOKS_VILLAGE_3,
            ITEMS_DISCIPLES_TOWER_4,
            DUNGEON_KEY,
        },
    },
    {
        MAP,
        {
            EVERYTHING,
        },
    },
    {
        BONE,
        {
            ITEMS_DUNGEON,
        },
    },
    {
        STAR_CREST,
        {
            ALL_TOWER_1,
            ITEMS_CATHEDRAL_1,
            ITEMS_CATHEDRAL_2,
            ITEMS_LAKMIRS_TOWER_1,
            BOOKS_LAKMIRS_TOWER_1,
            // ITEMS_LAKMIRS_TOWER_2,
        },
    },
    {
        IRON_BAR,
        {
            ITEMS_DUNGEON,
            ITEMS_SEWERS_1,
        },
    },
    {
        CROWBAR,
        {
            // Leaving the first tower without the Crowbar would lead to a soft-lock.
            // ALL_TOWER_1,
            ITEMS_CATHEDRAL_1,
        },
    },
    {
        HAIR_OF_GIANT,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ALL_VILLAGE,
            ALL_TOWER_3,
            ITEMS_DISCIPLES_TOWER_5,
            ITEMS_DRAGON_TOWER_1,
            BOOKS_DRAGON_TOWER_1,
            BOOKS_DRAGON_TOWER_2,
        },
    },
    {
        MUG,
        {
            ALL_TOWER_1,
            ITEMS_CATHEDRAL_1,
            ITEMS_CATHEDRAL_2,
            ITEMS_LAKMIRS_TOWER_1,
            BOOKS_LAKMIRS_TOWER_1,
            // ITEMS_LAKMIRS_TOWER_2,
        },
    },
    {
        WATER,
        {
            // Randomizing Mug + Water could lead to a soft-lock.
            WATER,
        },
    },
    {
        WATER_WITH_DRAGON_TEARS,
        {
            // Randomizing Mug + Water could lead to a soft-lock.
            WATER_WITH_DRAGON_TEARS,
        },
    },
    {
        STONE_OF_THIRST,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ALL_VILLAGE,
        },
    },
    {
        COIN_IN_PARK,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ITEMS_CATHEDRAL_3,
            BOOKS_CATHEDRAL_3,
            ITEMS_DISCIPLES_TOWER_3,
            ITEMS_VILLAGE_1,
            BOOKS_VILLAGE_1,
        },
    },
    {
        COIN_IN_PATHWAY_TO_PARK,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ITEMS_CATHEDRAL_3,
            BOOKS_CATHEDRAL_3,
            ITEMS_DISCIPLES_TOWER_3,
            ITEMS_VILLAGE_1,
            BOOKS_VILLAGE_1,
        },
    },
    {
        COIN_IN_EXCAVATION_AREA,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ITEMS_CATHEDRAL_3,
            BOOKS_CATHEDRAL_3,
            ITEMS_DISCIPLES_TOWER_3,
            ITEMS_VILLAGE_1,
            BOOKS_VILLAGE_1,
        },
    },
    {
        COIN_IN_GATE_KEEPERS_ROOM,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ITEMS_CATHEDRAL_3,
            BOOKS_CATHEDRAL_3,
            ITEMS_DISCIPLES_TOWER_3,
            ITEMS_VILLAGE_1,
            BOOKS_VILLAGE_1,
        },
    },
    {
        LOST_COIN,
        {
            // This coin does not appear in the game.
            LOST_COIN,
        },
    },
    {
        NAIL,
        {
            EVERYTHING,
        },
    },
    {
        BROOCH,
        {
            EVERYTHING,
        },
    },
    {
        JEWELRY_BOX,
        {
            EVERYTHING,
        },
    },
    {
        FRUIT,
        {
            EVERYTHING,
        },
    },
    {
        GAUNTLET,
        {
            EVERYTHING,
        },
    },
    {
        CUP,
        {
            EVERYTHING,
        },
    },
    {
        ARTWORK,
        {
            EVERYTHING,
        },
    },
    {
        POISONOUS_HERB,
        {
            EVERYTHING,
        },
    },
    {
        BRACELET,
        {
            EVERYTHING,
        },
    },
    {
        PRECIOUS_STONE,
        {
            EVERYTHING,
        },
    },
    {
        BROKEN_SWORD,
        {
            EVERYTHING,
        },
    },
    {
        QUILL,
        {
            EVERYTHING,
        },
    },
    {
        PLATE,
        {
            EVERYTHING,
        },
    },
    {
        BROKEN_LANCE,
        {
            EVERYTHING,
        },
    },
    // unused item id's
    {
        0x47, { },
    },
    {
        0x48, { },
    },
    {
        0x49, { },
    },
    {
        0x4a, { },
    },
    {
        DNARTH_FAMILY_CHRONICLES,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ALL_VILLAGE,
            ITEMS_TRIALS_1,
            BOOKS_TRIALS_1,
        },
    },
    {
        THE_FINAL_BATTLE,
        {
            EVERYTHING,
        },
    },
    {
        THE_SPEECHES_OF_LORD_JAIR,
        {
            EVERYTHING,
        },
    },
    {
        THE_ABYSS_OF_DARKNESS,
        {
            EVERYTHING,
        },
    },
    {
        THE_AGE_OF_ENLIGHTENMENT,
        {
            EVERYTHING,
        },
    },
    {
        THE_SECRETS_OF_THE_STAFF,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ALL_VILLAGE,
            ITEMS_TRIALS_1,
            BOOKS_TRIALS_1,
        },
    },
    {
        STUDENTS_DIARY,
        {
            ALL_TOWER_1,
            ITEMS_CATHEDRAL_1,
            ITEMS_CATHEDRAL_2,
            ITEMS_LAKMIRS_TOWER_1,
            BOOKS_LAKMIRS_TOWER_1,
            // ITEMS_LAKMIRS_TOWER_2,
        },
    },
    {
        ACOLYTES_DIARY,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ALL_VILLAGE,
            ITEMS_TRIALS_1,
            BOOKS_TRIALS_1,
        },
    },
    {
        PERSONAL_JOURNAL,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ITEMS_CATHEDRAL_3,
            BOOKS_CATHEDRAL_3,
            ITEMS_VILLAGE_1,
            BOOKS_VILLAGE_1,
            ITEMS_MERCHANT,
            ITEMS_VILLAGE_4,
        },
    },
    {
        MEMOIRS,
        {
            EVERYTHING,
        },
    },
    {
        NOVICES_JOURNAL,
        {
            EVERYTHING,
        },
    },
    {
        TRIALS_OF_THE_KINGDOM,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ALL_VILLAGE,
            ITEMS_TRIALS_1,
            BOOKS_TRIALS_1,
        },
    },
    {
        THE_BROTHERHOOD_REPORT,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ALL_VILLAGE,
            ITEMS_TRIALS_1,
            BOOKS_TRIALS_1,
        },
    },
    {
        THE_WRITINGS_OF_KONNOR,
        {
            EVERYTHING,
        },
    },
    {
        THE_HOUSE_OF_DRESLIN,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ALL_VILLAGE,
            ITEMS_TRIALS_1,
            BOOKS_TRIALS_1,
        },
    },
    {
        MEMORANDUM,
        {
            EVERYTHING,
        },
    },
    {
        THE_LAST_DRAGON,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ALL_VILLAGE,
            ITEMS_TRIALS_1,
            BOOKS_TRIALS_1,
        },
    },
    {
        OF_RIDING_DRAGONS,
        {
            EVERYTHING,
        },
    },
    {
        RESEARCH_LOG,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ALL_VILLAGE,
            ITEMS_TRIALS_1,
            BOOKS_TRIALS_1,
        },
    },
    {
        MUSINGS_OF_A_LUNATIC,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ALL_VILLAGE,
            ITEMS_TRIALS_1,
            BOOKS_TRIALS_1,
        },
    },
    {
        THE_BOOK_OF_ORDERS,
        {
            ITEMS_DUNGEON,
            ITEMS_SEWERS_1,
            ITEMS_SEWERS_2,
            BOOKS_SEWERS_2,
            ITEMS_DISCIPLES_TOWER_1,
            BOOKS_DISCIPLES_TOWER_1,
        },
    },
    {
        LAWS_OF_MAGIC,
        {
            ALL_TOWER_1,
        },
    },
    {
        FAMILY_DIARY,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ITEMS_CATHEDRAL_3,
            BOOKS_CATHEDRAL_3,
            ITEMS_DISCIPLES_TOWER_3,
            ITEMS_VILLAGE_1,
            BOOKS_VILLAGE_1,
            ITEMS_MERCHANT,
            ITEMS_VILLAGE_2,
            ITEMS_DISCIPLES_TOWER_4,
        },
    },
    {
        WORDS_OF_DNARTH,
        {
            EVERYTHING,
        },
    },
    {
        ARTIFACTS_OF_POWER,
        {
            ALL_TOWER_1,
        },
    },
    {
        MAGICAL_ELIXIRS,
        {
            ALL_TOWER_1,
            ITEMS_CATHEDRAL_1,
            ITEMS_CATHEDRAL_2,
            ITEMS_LAKMIRS_TOWER_1,
            BOOKS_LAKMIRS_TOWER_1,
        },
    },
    // unused book id's
    {
        0x65, { },
    },
    {
        0x66, { },
    },
    {
        0x67, { },
    },
    {
        JOURNAL,
        {
            EVERYTHING,
        },
    },
    {
        WATCHMANS_MEMO,
        {
            EVERYTHING,
        },
    },
    {
        REPORT,
        {
            ITEMS_DUNGEON,
            ITEMS_SEWERS_1,
            ITEMS_SEWERS_2,
            BOOKS_SEWERS_2,
            ITEMS_DISCIPLES_TOWER_1,
            BOOKS_DISCIPLES_TOWER_1,
        },
    },
    {
        OFFICIALS_ARTICLE,
        {
            // Leaving the first tower without the Rusty Key would lead to a soft-lock.
            // ALL_TOWER_1,
            ITEMS_CATHEDRAL_1,
            ITEMS_CATHEDRAL_2,
            ITEMS_LAKMIRS_TOWER_1,
            BOOKS_LAKMIRS_TOWER_1,
        },
    },
    {
        LECTURE_NOTES,
        {
            ALL_TOWER_1,
            ALL_TOWER_2,
            ALL_VILLAGE,
        },
    },
    {
        PERSONAL_LETTER,
        {
            EVERYTHING,
        },
    },
    {
        THE_INNER_CHAMBER,
        {
            ALL_TOWER_1,
            ITEMS_CATHEDRAL_1,
            ITEMS_CATHEDRAL_2,
            ITEMS_LAKMIRS_TOWER_1,
            BOOKS_LAKMIRS_TOWER_1,
            // ITEMS_LAKMIRS_TOWER_2,
            ITEMS_LAKMIRS_TOWER_3,
            BOOKS_LAKMIRS_TOWER_3,
        },
    },
    {
        TRAVELOGUE,
        {
            EVERYTHING,
        },
    },
    {
        TRAVEL_GUIDE,
        {
            EVERYTHING,
        },
    },
    {
        PETITION,
        {
            EVERYTHING,
        },
    },
    {
        RECEIPT,
        {
            EVERYTHING,
        },
    },
    {
        PERSONAL_NOTE,
        {
            EVERYTHING,
        },
    },
};

#pragma clang diagnostic pop

const char itemNames[BOOK_END][32] = {
    "Empty",
    "Crest Key",
    "Bottle of Oil",
    "Fragments of a Crest",
    "Dragon Tears",
    "Pixie Flute",
    "Treasure",
    "Rusty Key",
    "Ornate Key",
    "Ring of the Kingdom",
    "Orb",
    "Golden Key",
    "Liquid Sunset",
    "Night Elixir",
    "Forest Nectar",
    "Primitive Man Statue",
    "Apeman Sculpture",
    "Fairy Sculpture",
    "Elf Statue",
    "Ancient Coin",
    "Pickax",
    "Ring of the Dead",
    "Blue Ring",
    "Green Ring",
    "Lever",
    "Slipper",
    "Dirty Slipper",
    "Pair of Slippers",
    "Jezibel's Pendant",
    "Staff of Ages",
    "Rope",
    "Cemetery Key",
    "Flower",
    "Flint",
    "Fang",
    "Dragon Eye",
    "Dragon Flute",
    "Burning Candle",
    "Chipped Violin",
    "Violin without Strings",
    "Broken Violin",
    "Dungeon Key",
    "Map",
    "Bone",
    "Star Crest",
    "Iron Bar",
    "Crowbar",
    "Hair of Giant",
    "Mug",
    "Water",
    "Water with Dragon Tears",
    "Stone of Thirst",
    "Coin in Park",
    "Coin in Pathway to Park",
    "Coin in Excavation Area",
    "Coin in Gate Keeper's Room",
    "Lost Coin",
    "Nail",
    "Brooch",
    "Jewelry Box",
    "Fruit",
    "Gauntlet",
    "Cup",
    "Artwork",
    "Poisonous Herb",
    "Bracelet",
    "Precious Stone",
    "Broken Sword",
    "Quill",
    "Plate",
    "Broken Lance",
    "",
    "",
    "",
    "",
    "D'Narth Family Chronicles",
    "The Final Battle",
    "The Speeches of Lord Jair",
    "The Abyss of Darkness", // "Blank Blue Book"
    "The Age of Enlightenment", // "Blank Green Book"
    "The Secrets of the Staff", // "Blank Red Book"
    "Student's Diary",
    "Acolyte's Diary",
    "Personal Journal",
    "Memoirs",
    "Novice's Journal",
    "The Trials of the Kingdom",
    "The Brotherhood Report",
    "The Writings of Konnor",
    "The House of Dreslin",
    "Memorandum",
    "The Last Dragon",
    "Of Riding Dragons",
    "Research Log",
    "Musings of a Lunatic",
    "The Book of Orders",
    "Laws of Magic",
    "Family Diary",
    "Words of D'Narth",
    "Artifacts of Power",
    "Magical Elixirs",
    "",
    "",
    "",
    "Journal",
    "Watchman's Memo",
    "Report",
    "Official's Article",
    "Lecture Notes",
    "Personal Letter",
    "The Inner Chamber",
    "Travelogue",
    "Travel Guide",
    "Petition",
    "Receipt",
    "Personal Note",
};

static const itemId_t everyLocation[BOOK_END] = {
    EVERYTHING,
};

int compareItems(const void * a, const void * b) {
    const item_t * item1 = (const item_t *) a;
    const item_t * item2 = (const item_t *) b;

    if (item1->numPossibilities == item2->numPossibilities) {
        return item1->id - item2->id;
    }

    return item1->numPossibilities - item2->numPossibilities;
}

void preprocessItems(shuffleMode_t mode) {
    for (itemId_t id = 0; id < BOOK_END; ++id) {
        if (mode == MODE_SHUFFLE_BOOKS_NO_LOGIC && isBook(id)) {
            memcpy(initialItems[id].possibleLocations, everyLocation, BOOK_END * sizeof(itemId_t));
        }

        int num = 0;

        for (int i = 0; i < BOOK_END; ++i, ++num) {
            if (!initialItems[id].possibleLocations[i]) {
                break;
            }
        }

        initialItems[id].numPossibilities = num;
    }
}

bool isValidItem(itemId_t id) {
    return id >= ITEM_START && id < BOOK_END && itemNames[id][0] != '\0';
}

bool isItem(itemId_t id) {
    return id >= ITEM_START && id < ITEM_END && itemNames[id][0] != '\0';
}

bool isBook(itemId_t id) {
    return id >= BOOK_START && id < BOOK_END && itemNames[id][0] != '\0';
}