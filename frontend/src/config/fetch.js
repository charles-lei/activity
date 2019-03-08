import { baseUrl } from './env'

export default async(url, data = {}) => {
  url = baseUrl + url
  return new Promise((resolve, reject) => {
    let requestObj = new XMLHttpRequest()
    // requestObj.withCredentials = true
    let sendData = JSON.stringify(data)

    requestObj.open('POST', url, true)
    requestObj.send(sendData)

    requestObj.onreadystatechange = () => {
      if (requestObj.readyState === 4) {
        if (requestObj.status === 200 || requestObj.status === 201) {
          let obj = requestObj.response
          if (typeof obj !== 'object') {
            obj = JSON.parse(obj)
          }
          resolve(obj)
        } else {
          reject(requestObj)
        }
      }
    }
  })
}
