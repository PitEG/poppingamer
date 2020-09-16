#pragma once

namespace pg {
  template<typename T>
    struct Component {
      T             component; //the actual component
      unsigned int  entityID;  //the entity associated with this
      bool          active;    //if the entity is active

      Component(T c, unsigned int entityId, bool active) 
        : component(c), entityID(entityId), active(active) {
        }
    };
}
