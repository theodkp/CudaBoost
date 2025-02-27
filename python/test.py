import sys
import numpy as np
sys.path.append("build/Debug")
import matplotlib.pyplot as plt

import gbm_pybind as gbm

params = {'n_estimators': 100, 'max_depth': 3, 'learning_rate': 0.1, "n_bins":0, 'device': "gpu"}

model = gbm.Regressor(**params)








### y :expects 1d array
np.random.seed(42)

X = np.linspace(0, 10, 100)
y = 3.0 * X + np.random.randn(100) * 2


### X :expects 2d array
print(X.reshape(-1,1))
# model.fit(X,y)

X_test = np.linspace(3, 7, 100)


# y_pred = model.predict(X_test)


# mse = np.mean((y_pred - y) ** 2)
# print("Training MSE:", mse)