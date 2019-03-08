<template>
  <div class="container">
      <header class="header">活动报名统计
      <div v-if="currentAccount"></div>
      <div v-else @click="login" style="margin-left: auto;"  class="login">登录</div>
     <!--  <img src="../assets/down.png" class="down" alt="" style="margin-left: 10px"> -->
      <div v-if="currentAccount" style="margin-left: auto;" @click="logout">登出</div>
      </header>
        <main>
          <div class="main-container">
            <div class="setword">
              <input type="text" v-model="currentAccount" disabled />
              <button @click="signup">报名</button>
            </div>
            <div class="tips">
              <div>
                 <p>报名列表：</p>
                <ul v-for="(item, index) in players" :key="index">
                  {{item.attendee + '  ' + item.time}}
                </ul>
              </div>
            </div>
          </div>
        </main>
        <footer>使用前请安装 Scatter 钱包</footer>   
  </div>
</template>

<script>
import Eos from 'eosjs'
import ScatterJS from 'scatterjs-core'
import ScatterEOS from 'scatterjs-plugin-eosjs'
import {getPlayerList} from '../api'

ScatterJS.plugins(new ScatterEOS())

const network = {
  blockchain: 'eos',
  host: '127.0.0.1',
  port: 8888,
  protocol: 'http',
  chainId: 'cf057bbfb72640471fd910bcb67639c22df9f92470936cddc1ade0e2f2e7dc4f'
}

// Put eosClient in data will case a weird problem in scatter-desktop.
let eosClient = null

const requiredFields = { accounts: [network] }

export default {
  name: 'Activity',
  data() {
    return {
      currentAccount: null,
      scatter: null,
      players: []
    }
  },
  created() {
    this.login()
    setInterval(this.getPlayers, 1000)
  },
  methods: {
    login() {
      ScatterJS.scatter.connect('activity').then((connected) => {
        ScatterJS.scatter.getIdentity(requiredFields).then(() => {
          const account = ScatterJS.scatter.identity.accounts.find(
            x => x.blockchain === 'eos'
          )
          this.currentAccount = account.name
          this.scatter = ScatterJS.scatter
          eosClient = ScatterJS.scatter.eos(network, Eos)
          this.$emit('login', this.currentAccount)
        }).catch(err => {
          console.log('login error' + err)
        })
      })
    },
    logout() {
      this.scatter.forgetIdentity()
      this.currentAccount = null
    },
    signup() {
      if (!this.currentAccount) {
        return alert('请先登录')
      }
      console.log(this.currentAccount)
      eosClient.transaction({
        actions: [
          {
            account: 'demouser1111',
            name: 'signup',
            authorization: [
              {
                actor: this.currentAccount,
                permission: 'active'
              }
            ],
            data: {
              user: this.currentAccount
            }
          }
        ]
      }).then(data => {
        console.log(data)
        alert('报名成功')
      }).catch((err) => {
        if (err.includes('already signed')) {
          return alert('已经报名！')
        }
        console.log(err)
        alert('报名失败')
      })
    },
    getPlayers() {
      getPlayerList().then(data => {
        console.log('fsadfdsf')
        this.players = data
      })
    }
  }
}
</script>

<style>
.container{
    height: 100%;
    display: flex;
    flex-direction: column;
    /* background-color: #202c2f; */
    background: #85144b; /* Safari 5.1 - 6.0 */
}

.header{
   display: flex;
    height: 20px;
    line-height: 20px;
    padding: 0 10px;
    /* background: #f8f8f8; */
    color: #FF851B;
    /* box-shadow: 0 0 5px #ccc; */
    border-bottom: 1px solid #FF851B;
}
.container main{
    flex: 1;
    display: flex;
    flex-direction: column;
}
.main-container{
    width: 70%;
    margin: 20px auto;
    display: flex;
    flex: initial;
    flex-direction: column;
    justify-content: space-around;
}
.showword{
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-self: center;
    font-size: 14px;
    color: #FF851B;
}
.showword div{
    font-size: 40px;
    text-align: center;
    color: #eee;
}
.showword p{
    text-align: center;
}
.showword p span:nth-child(1){
    margin-right: 30px;
}
.setword{
    display: flex;
    align-items: center;
}
.setword input{
    flex: 1;
    padding: 0 20px;
    margin-right: 20px;
    outline: none;
    border: 1px solid #eee;
    border-radius: 3px;
    transition: all ease .5s;
}
.setword input:focus{
    border-color: #00d9ff;
    box-shadow: 0 0 5px 2px #00d9ff;
}
.setword input:hover{
    border-color: #00d9ff;
}
.setword button{
    border: 0;
    background: #333;
    color: #FF851B;
    border-radius: 3px;
    transition: all ease .5s;
    cursor: pointer;
    outline: none;
}
.setword button:hover{
    background: #000;
    color: #FF851B;
}

.tips{
    margin-top: 10px;
    color: #FF851B;
}
ul{
    padding-left: 20px;
}
footer{
    display: flex;
    justify-content: center;
    align-items: center;
    height: 20px;
    line-break: 20px;
    /* background: #f8f8f8; */
    color: #FF851B;
    text-align: center;
    border-top: 1px solid #FF851B;
}
a{
    text-decoration-line: none;
}
footer a{
    color: #FF851B;
    margin-left: 10px;
}
.loading{
    position: fixed;
    width: 100vw;
    height: 100vh;
    top: 0;
    left: 0;
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
    background-color: rgba(0, 0, 0, .65);
    z-index: -1;
    opacity: 0;
    transition: all ease 2s;
    color: #eee;
}
.loading.show{
    z-index: 999;
    opacity: 1;
}
.loading image{
    margin-bottom: 50px;
}
</style>
