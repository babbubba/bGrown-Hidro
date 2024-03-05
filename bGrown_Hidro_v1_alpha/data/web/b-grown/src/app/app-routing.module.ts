import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { PhMeterComponent } from './ph-meter/ph-meter.component';

const routes: Routes = [
  {
    path:'ph-meter',
    component: PhMeterComponent
  }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
