#include "marconetlist.h"
#include "schematic.h"

namespace qucs {
namespace exports {

// --- MarcoNetlistConverter ---
QString
MarcoNetlistConverter::convertToMarcoNetlist(Schematic* schematic) {

    QString result = QString(   "# MarcoNetlist v0.1\n"
                                "# " + schematic->Frame_Text0 + "\n\n");

    // write down all components
    Component* component = schematic->Components->first();
    while(component != nullptr){

        result = result + component->convertToMarcoNetlist() + "\n";

        // next iteration
        component = schematic->Components->next();
    }

    // write down all wires
    // TODO
    return result;
}

} // end namespace exports
} // end namespace qucs
