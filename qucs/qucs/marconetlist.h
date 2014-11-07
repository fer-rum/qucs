#ifndef MARCONETLIST_H
#define MARCONETLIST_H

#include <QString>


class Schematic;

namespace qucs {
namespace exports{

/**
 * @brief The MarcoNetlistConverter class offers facilities to create a netlist that has been derived from a Schematic.
 * @author Fredo Erxleben
 *
 *  The current netlist-notation version is 0.1
 *
 * This class follows a factory pattern.
 *
 * MarcoNetlist0.1 notation is as follows:
 * <p>
 * There is only a global namespace for all names.
 * Whitespaces (except for line breaks) are ignored.
 * Lines beginning with &#35; (double-cross) are comments.
 * <ul>
 *  <li>
 *      A <i>component name</i> is a unique alphanumerical string that identifies a component.
 *  </li>
 *  <li>
 *      A <i>port name</i> is a unique alphanumerical string associated with the port of a component.
 *      Port names are prefixed with the appropriate component identifier, followed by an underscore.
 *  </li>
 *  <li>
 *      There are three types of ports: <b>input</b>, <b>selection</b>, <b>output</b>.
 *      <ul>
 *          <li>Input port names begin with <i>in</i></li>
 *          <li>Selection port names begin with <i>sel</i></li>
 *          <li>Output port names begin with <i>out</i></li>
 *      </ul>
 *  </li>
 *  <li>
 *      A <i>port group</i> is a ordered list of port names separated by a comma.
 *      All ports of a group must be of the same type.
 *      A port group may be empty.
 *  </li>
 *  <li>
 *      The order within a <i>port group</i> is from most significant bit (MSB) to least significant bit (LSB).
 *      The LSBs port name is postfixed with <i>0</i>.
 *      With increasing significance the postfix of the port of a group are to be incremented by 1.
 *  </li>
 *  <li>
 *      A function represents the inner workings of a component.
 *      The notation syntax for a function is </br>
 *          <i>FUNCTION_NAME</i>(<i>output port group</i>:<i>selection port group</i>:<i>input port group</i>)</br>
 *      Each function goes on a seperate line.
 *  </li>
 * </ul>
 */
class MarcoNetlistConverter{
public:

    static QString convertToMarcoNetlist(Schematic* schematic);
};

} // end namespace exports
} // end namespace qucs



#endif // MARCONETLIST_H
