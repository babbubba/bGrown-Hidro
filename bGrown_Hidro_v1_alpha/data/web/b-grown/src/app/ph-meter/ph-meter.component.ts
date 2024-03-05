import { Component, OnInit } from '@angular/core';
import { SensorsService } from '../services/sensors.service';

@Component({
  selector: 'app-ph-meter',
  templateUrl: './ph-meter.component.html',
  styleUrls: ['./ph-meter.component.less']
})
export class PhMeterComponent implements OnInit {
  getPhSensorValue$ = this.sensors.getPhSensorValue();

  constructor(private sensors: SensorsService) {}

  ngOnInit(): void {

  }

}
