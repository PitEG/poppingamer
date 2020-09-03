#pragma once

namespace pg {
  template<typename T>
    struct Component {
      T             component; //the actual component
      unsigned int  entityId;  //the entity associated with this
      bool          active;    //if the entity is active

      Component(T c, unsigned int entityId, bool active) 
        : component(c), entityId(entityId), active(active) {
        }
    };
}
