import sys
import numpy as np
sys.path.append("build/Debug")
import matplotlib.pyplot as plt

import gbm_pybind as gbm

params = {'n_estimators': 1000, 'max_depth': 1, 'learning_rate': 0.03}

model = gbm.Regressor(**params)


np.random.seed(42)

### x :expects 2d array
X = np.linspace(0, 10, 100)
X = X.astype(np.float32)

### y :expects 1d array
y = 3.0 * X + np.random.randn(100) * 2
y = y.astype(np.float32)

X = X.reshape(-1,1)
y = y.ravel()

# fit model
model.fit(X,y)

X_test = np.linspace(3, 7, 10)
X_test = X_test.reshape(-1,1)
X_test = X_test.astype(np.float32)


y_test = 3.0 * X_test + np.random.randn(10) * 2
y_test = y_test.astype(np.float32) 
y_test = y_test.ravel()


#predict on unseen data
y_pred = model.predict(X_test)



def calculate_mse(predictions, targets):
    squared_errors = [(pred - target) ** 2 for pred, target in zip(predictions, targets)]
    return sum(squared_errors) / len(predictions)



mse = calculate_mse(y_pred, y_test)
print("Training MSE:", mse)



