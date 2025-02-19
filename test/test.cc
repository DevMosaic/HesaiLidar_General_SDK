/******************************************************************************
 * Copyright 2019 The Hesai Technology Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include "pandarGeneral_sdk/pandarGeneral_sdk.h"
#include <iostream>
#define PRINT_FLAG
// #define PCD_FILE_WRITE_FLAG 

int frameItem = 0;

void gpsCallback(int timestamp) {
#ifdef PRINT_FLAG
    printf("gps: %d\n", timestamp);
#endif    
}

void lidarCallback(std::shared_ptr<PPointCloud> cld, double timestamp) {
#ifdef PRINT_FLAG
    printf("timestamp: %lf,point_size: %ld\n", timestamp, cld->points.size());
#endif
#ifdef PCD_FILE_WRITE_FLAG
    frameItem++;
    if(10 == frameItem) {
        printf("write pcd file\n");
        pcl::PCDWriter writer;
        writer.write("PandarPointXYZI.pcd", *cld);
    }
#endif
}
void lidarAlgorithmCallback(HS_Object3D_Object_List* object_t) {
    HS_Object3D_Object* object;
#ifdef PRINT_FLAG
      printf("----------------------\n");
      printf("total objects: %d\n",object_t->valid_size);
      for (int i = 0; i < object_t->valid_size; i++) {
          object = &object_t->data[i];
          printf("id: %u, type: %u\n",object->data.id, object->type);
      }
      printf("----------------------\n");
#endif
}

int main(int argc, char** argv) {
  PandarGeneralSDK pandarGeneral(std::string("10.115.1.180"), 2368, 0, 10110, \
      lidarCallback, lidarAlgorithmCallback, gpsCallback, 0, 0, 1, std::string("Pandar64"), std::string("frame_id"), "", std::string("../com_github_HesaiLidar_General_SDK/Pandar64.csv"), "", false);


  pandarGeneral.Start();
  int i = 0;
  while (i < 4) {
    sleep(1);
    i++;
  }


  pandarGeneral.Stop();

  return 0;
}
