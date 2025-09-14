<template>
	<view class="content">
		<view class="">温度{{temp}}°C</view>
		<view class="">湿度{{humi}} %</view>
		<switch :checked="led" @change=""/>
	</view>
</template>

<script>
	const{createCommonToken} = require('@/key.js')
	export default {
		data() {
			return {
				temp:'11',
				humi:'22',
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
						console.log(res.data.data[0].value);
				    }
				});
				
			}
		}
	}
</script>

<style>
	.content {
		display: flex;
		flex-direction: column;
		align-items: center;
		justify-content: center;
	}

	.logo {
		height: 200rpx;
		width: 200rpx;
		margin-top: 200rpx;
		margin-left: auto;
		margin-right: auto;
		margin-bottom: 50rpx;
	}

	.text-area {
		display: flex;
		justify-content: center;
	}

	.title {
		font-size: 36rpx;
		color: #8f8f94;
	}
</style>
