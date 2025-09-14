<template>
	
	<view class="wrap">
		<view class="dev-area">
			
			<view class="dev-card">
				<view class="">
					<view class="dev-name">温度</view>
					<image class="dev-log" src="/static/temp.png"></image>
				</view>
				<view class="dev-data">{{temp}}°C</view>
			</view>
			
			<view class="dev-card">
				<view class="">
					<view class="dev-name">湿度</view>
					<image class="dev-log" src="/static/humi.png"></image>
				</view>
				<view class="dev-data">{{humi}} %</view>
			</view>
			
			<view class="dev-card">
				<view class="">
					<view class="dev-name">光照</view>
					<image class="dev-log" src="/static/light.png"></image>
				</view>
				<view class="dev-data">833 lx</view>
			</view>
			
			<view class="dev-card">
				<view class="">
					<view class="dev-name">台灯</view>
					<image class="dev-log" src="/static/led.png"></image>
				</view>
				<switch :checked="led" @change="onLedSwitch" color="#038021"/></div>
			</view>
		</view>
	</view>	
</template>

<script>
	const{createCommonToken} = require('@/key.js')
	export default {
		data() {
			return {
				temp:'50',
				humi:'50',
				led:true,
				token:'',
			}
		},
		onLoad() {
			const params = {
				author_key:'nQHKhqcj9ROk1HSM1lhyV8gSytu2fbK3wfKahL5bDdrW4VQ6oZUbd2Y/16wUcAZC',
				version:'2022-05-01',
				user_id:'464317'
				}
		
			this.token = createCommonToken(params);
			
			// console.log(this.token)
		},
		
		onShow() {
			this.fetchDevData();
			setInterval(() => {
				this.fetchDevData();
			},500)
		},
		methods: {
			fetchDevData(){
				uni.request({
				    url: 'https://iot-api.heclouds.com/thingmodel/query-device-property', 
					method:'GET',
				    data: {
						product_id: '1c6LfBoi8J',
						device_name: 'd1'
				    },
				    header: {
				        'authorization': this.token
				    },
				    success: (res) => {
				        console.log(res.data);
						this.humi = res.data.data[0].value;
						this.temp = res.data.data[2].value;
						this.led = res.data.data[1].value === 'true' ? true : false;
				    }
				});
			},
			
			onLedSwitch(event){
				let led_value = event.detail.value;
	
				uni.request({
				    url: 'https://iot-api.heclouds.com/thingmodel/set-device-property', 
					method:'POST',
				    data: {
						product_id: '1c6LfBoi8J',
						device_name: 'd1',
						params: {"led": led_value}
				    },
				    header: {
				        'authorization': this.token
				    },
				    success: (res) => {
				        console.log('LED' + (led_value ? 'ON' : 'OFF') + '！');
				    }
				});
			}
		}
	}
</script>

<style>
	
	.wrap {
		padding: 30rpx;
	}
	
	.dev-area {
		display: flex;
		justify-content: space-between;
		flex-wrap: wrap;
	}

	.dev-card {
		height:150rpx;
		width: 320rpx;
		border-radius: 30rpx;
		display: flex;
		justify-content: space-around;
		align-items: center;
		margin-top: 30rpx;
		box-shadow: 0 0 15rpx #ccc;
	}
	
	.dev-name{
		font-size: 20rpx;
		color: #8f8f94;
		text-align: center;
	}
	
	.dev-data{
		font-size: 50rpx;
		text-align: center;
	}
	
	.dev-log {
		height: 70rpx;
		width: 70rpx;
		margin-top: 10rpx;
	}

	.title {
		font-size: 36rpx;
		color: #8f8f94;
	}
</style>
