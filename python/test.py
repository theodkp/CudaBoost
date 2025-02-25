import sys
sys.path.append("build/Debug")

import gbm_pybind as gbm

## Load data

data = gbm.load_csv("data/iris.csv")

print(data.data)

## Create a model

# params = {'n_estimators': 100, 'max_depth': 3, 'learning_rate': 0.1, 'device': "gpu"}
# model = gbm.Regressor(**params)
## model = gbm.Classifier()

## model.fit(X_train,y_train)

## model.predict(X_test)
