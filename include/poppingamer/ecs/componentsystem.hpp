#pragma once 

#include "poppingamer/ecs/component.hpp"

/*
 * TODO FIGURE THIS OUT
 */
namespace pg {
  class ComponentSystem {
  protected: 
    ComponentSystem();
    virtual ~ComponentSystem();

    virtual void UpdateComponents() = 0;

  };


  /*
   * EXAMPLE
   */

  class ComponentSystemExample : public ComponentSystem {
  private:
    //List of components by type
    /* transforms
     * run controllers
     * collision boxes 
     */
  public:
    ComponentSystemExample() {
      //initialize list of components
      /*
       *
       */
    }
    ~ComponentSystemExample();

    virtual void UpdateComponents() override {
      //run components in a specific order
      /* run transforms
       * run controllers 
       * run collision boxes
       */
    }
  };
}
