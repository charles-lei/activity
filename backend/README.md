## 进入目录

```
cd activity/backend/activity
```

## 编译

```
eosio-cpp -abigen activity.cpp -o activity.wasm
```

## 部署

```
cleos set contract activity ../activity -p demouser1111@active
```