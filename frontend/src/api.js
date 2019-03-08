
import fetch from './config/fetch'
import {signTableOptions} from './config/env'

export const getPlayerList = async function() {
  let user = await fetch('/v1/chain/get_table_rows', signTableOptions, 'POST')
  return user.rows
}
