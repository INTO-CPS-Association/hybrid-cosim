/* External objects file */
#include "StategraphSample_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* Has to be performed after _init.xml file has been read */
void StategraphSample_callExternalObjectConstructors(DATA *data, threadData_t *threadData)
{
  /* data->simulationInfo->extObjs = NULL; */
  infoStreamPrint(LOG_DEBUG, 0, "call external Object Constructors");
  infoStreamPrint(LOG_DEBUG, 0, "call external Object Constructors finished");
}

void StategraphSample_callExternalObjectDestructors(DATA *data, threadData_t *threadData)
{
  if(data->simulationInfo->extObjs)
  {
    free(data->simulationInfo->extObjs);
    data->simulationInfo->extObjs = 0;
  }
}
#if defined(__cplusplus)
}
#endif

