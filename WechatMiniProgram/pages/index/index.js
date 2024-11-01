// index.js
const defaultAvatarUrl = 'https://mmbiz.qpic.cn/mmbiz/icTdbqWNOwNRna42FI242Lcia07jQodd2FJGIYQfG0LAJGFxM4FbnQP6yfMxBgJ0F3YRqJCJ1aPAK2dQagdusBZg/0'

var app = getApp();
var mqtt = require('../../utils/mqtt.min.js');
var client = null;

Page({
  data: {
	title:'MQTT服务器订阅',
	welcome:'Welcome To Deralive\'s Home',
	location:'广西省 北海市',
	temperature:27,

	isConnect:false,
	mqttContontDialog:false,
	// Sensor Data:
	sensorList: [
		{
		  img: "/images/Temperature.jpg",
		  name: "DHT22",
		  parameter: "温度",
		  value: 0,
		  unit: "°C",
		  idx: 0,
		},
		{
		  img: "/images/Humidity.jpg",
		  name: "DHT22",
		  parameter: "湿度",
		  value: 0,
		  unit: "%rh",
		  // isPass: true,
		  idx: 1,
		},
		{
		  img: "/images/Brightness.jpg",
		  name: "LM393",
		  parameter: "光强",
		  value: 0,
		  unit: "lx",
		  idx: 2,
		},
		{
		  img: "/images/Smoke.jpg",
		  name: "MQ135",
		  parameter: "烟雾",
		  value: 0,
		  unit: "ppm",
		  idx: 3,
		},
	  ],
	// Connect MQTT
	address:'//mqtts.heclouds.com/mqtt',
	port:'8084',
	clientId:'DHT22',
	username:'W9TI0JaXlu',
	password:'VzZrREE0T2hYeDZ0dDFQSUZZWWRIZ29yMGxrRUdGY2g=',
  	},

  	onLoad() {
		this.getInfo();
		this.startAutoUpdate();
	},

	onUnload() {
		if (this.data.updateInterval) {
			clearInterval(this.data.updateInterval);
		}
	},

	startAutoUpdate() {
		const that = this;
		const interval = setInterval(() => {
			that.getInfo();
		}, 3000);
		this.setData({ updateInterval: interval});
	},

	getInfo() {
		let that = this;
		wx.request({
			url: "https://iot-api.heclouds.com/thingmodel/query-device-property?product_id=W9TI0JaXlu&device_name=DHT22",
			header: {
				"authorization": "version=2018-10-31&res=products%2FW9TI0JaXlu%2Fdevices%2FDHT22&et=1759306118&method=md5&sign=JRsZv0peZQOTmr7Eg8lGJg%3D%3D"
			},
			method: "GET",
			success: res => {
				console.log("获取成功", res);

				const sensorList = that.data.sensorList;
				sensorList[0].value = res.data.data[5].value;
				sensorList[1].value = res.data.data[1].value;
				sensorList[2].value = res.data.data[0].value;
				sensorList[3].value = res.data.data[4].value;

				this.setData({
					sensorList: sensorList
				});
			},
			fail: function (res) {
				wx.showToast({
				  title: '系统错误'
				});
			  },
			  complete: function (res) {
				wx.hideLoading();
			  }
		});
	  },
	
	   onledsChange(event){
		const that = this
		console.log(event.detail.value);
		const sw = event.detail.value
		that.setData({leds:sw})
	
		if(sw){
		  wx.request({
			url: 'https://iot-api.heclouds.com/thingmodel/query-device-property?product_id=W9TI0JaXlu&device_name=DHT22',
			method: 'POST',  /* HTTP 请求方法:上传 */
			header: {
				"authorization": "version=2018-10-31&res=products%2FW9TI0JaXlu%2Fdevices%2FDHT22&et=1759306118&method=md5&sign=JRsZv0peZQOTmr7Eg8lGJg%3D%3D"
			},
			 success(res){
			   console.log("成功",res.data)
			 },
			 fail(res){
			   console.log("失败",res)
			 }
		   })
		}
	  },
});
