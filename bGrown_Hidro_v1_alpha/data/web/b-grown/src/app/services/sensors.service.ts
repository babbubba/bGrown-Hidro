import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Injectable, OnInit } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class SensorsService {

  constructor(private http: HttpClient) { }

  getPhSensorValue(): any {

    const headers = new HttpHeaders()
      .set('content-type', 'application/json,text/html,application/xhtml+xml,application/xml;')
      .set('Accept-Encoding', 'gzip, deflate')
      .set('Access-Control-Allow-Origin', '*');
    return this.http.get("http://bhome.zapto.org:9999/ph", {headers: headers});
  }


}
