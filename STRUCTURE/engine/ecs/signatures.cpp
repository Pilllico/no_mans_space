#include "entity.h"
#include "transform.h"
#include "physics.h"
#include "transformmanager.h"

// Component
bitmap Transform::componentSignature = bitmap("00000001");
bitmap Physics::componentSignature = bitmap("00001000");
