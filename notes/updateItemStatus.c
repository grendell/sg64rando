uint8_t * inventoryStatus;
uint8_t * inventory;
uint8_t inventorySize;

const uint8_t STATUS_SET_ALL = 0u;
const uint8_t STATUS_CLEAR_ALL = 1u << 6;

const uint8_t STATUS_FLAG_UNKNOWN = 1u << 0; // seems to only be set on a simple pickup interaction
const uint8_t STATUS_FLAG_IN_INVENTORY = 1u << 1;
const uint8_t STATUS_FLAG_IN_WORLD = 1u << 2;
const uint8_t STATUS_FLAG_EQUIPPED = 1u << 5;
const uint8_t STATUS_FLAG_CLEAR_ACTIONS = 1u << 7;

void updateItemStatus(uint16_t itemCode) {
    uint8_t itemId = itemCode & 0xff;
    uint8_t itemAction = (itemCode & 0xff00) >> 8;

    if (itemAction == SET_ALL) {
        inventoryStatus[itemId] = 0xffu;
    } else if (itemAction == CLEAR_ALL) {
        inventoryStatus[itemId] = 0u;
    } else if ((itemAction & STATUS_FLAG_CLEAR_ACTIONS) == 0u) {
        inventoryStatus[itemId] |= itemAction; // set bits in itemAction
    } else {
        // inventoryStatus[itemId] &= (0xff - (itemAction & 0x7f));
        inventoryStatus[itemId] &= ~(itemAction & 0x7fu); // clear bits in itemAction
    }

    uint16_t index = 0u;
    if (inventorySize != 0u) { // search for item in inventory
        do {
            if (inventory[index] == itemId) {
                break;
            }
            ++index;
        } while (index < inventorySize);
    }

    if (inventoryStatus[itemId] == 0u) {
        if (index != inventorySize) { // item was found in inventory
            if (index < inventorySize) {
                do {
                    inventory[index] = inventory[index + 1]; // shift inventory items up, removing item
                    ++index;
                } while (index < inventorySize);
            }
            --inventorySize;
        }
    } else if (index == inventorySize) { // existing status but item was not found in inventory
        for (; index > 0u; --index) {
            inventory[index] = inventory[index - 1]; // shift all inventory items down
        }
        ++inventorySize;
        *inventory = itemId; // update first inventory slot with item
    }
}