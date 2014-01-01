/*

  ucg_box.c

  Universal uC Color Graphics Library
  
  Copyright (c) 2013, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list 
    of conditions and the following disclaimer.
    
  * Redistributions in binary form must reproduce the above copyright notice, this 
    list of conditions and the following disclaimer in the documentation and/or other 
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
  
*/

#include "ucg.h"

ucg_ccs_t ucg_ccs_box[6];	/* color component sliders used by GradientBox */

void ucg_DrawGradientBox(ucg_t *ucg, ucg_int_t x, ucg_int_t y, ucg_int_t w, ucg_int_t h)
{
  uint8_t i;
  
  /* Setup ccs for l90se. This will be updated by ucg_clip_l90se if required */

  //printf("%d %d %d\n", ucg->arg.rgb[3].color[0], ucg->arg.rgb[3].color[1], ucg->arg.rgb[3].color[2]);
  
  for ( i = 0; i < 3; i++ )
  {
    ucg_ccs_init(ucg_ccs_box+i, ucg->arg.rgb[0].color[i], ucg->arg.rgb[2].color[i], h);
    ucg_ccs_init(ucg_ccs_box+i+3, ucg->arg.rgb[1].color[i], ucg->arg.rgb[3].color[i], h);
  }
  
  
  while( h > 0 )
  {
    ucg->arg.rgb[0].color[0] = ucg_ccs_box[0].current;
    ucg->arg.rgb[0].color[1] = ucg_ccs_box[1].current;
    ucg->arg.rgb[0].color[2] = ucg_ccs_box[2].current;
    ucg->arg.rgb[1].color[0] = ucg_ccs_box[3].current;
    ucg->arg.rgb[1].color[1] = ucg_ccs_box[4].current;
    ucg->arg.rgb[1].color[2] = ucg_ccs_box[5].current;
    //printf("%d %d %d\n", ucg_ccs_box[0].current, ucg_ccs_box[1].current, ucg_ccs_box[2].current);
    //printf("%d %d %d\n", ucg_ccs_box[3].current, ucg_ccs_box[4].current, ucg_ccs_box[5].current);
    ucg->arg.pixel.pos.x = x;
    ucg->arg.pixel.pos.y = y;
    ucg->arg.len = w;
    ucg->arg.dir = 0;
    ucg_DrawL90SEWithArg(ucg);
    for ( i = 0; i < 6; i++ )
      ucg_ccs_step(ucg_ccs_box+i);
    h--;
    y++;
  }
}