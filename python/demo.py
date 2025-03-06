import sys
import numpy as np
sys.path.append("build/Debug")
import matplotlib.pyplot as plt

import gbm_pybind as gbm

params = {'n_estimators': 1000, 'max_depth': 2, 'learning_rate': 0.01}

model = gbm.Regressor(**params)


np.random.seed(42)

### x :expects 2d array
X = np.linspace(0, 10, 100)
X = X.astype(np.float32)

### y :expects 1d array
y = (
    3.0 * np.sin(X) + 0.2 * X**2 + np.random.randn(100) * 0.5  
)
y = y.astype(np.float32)

X = X.reshape(-1,1)
y = y.ravel()

model.fit(X,y)

X_test = np.linspace(0, 10, 10) 
X_test = X_test.reshape(-1,1)
X_test = X_test.astype(np.float32)

y_test = (3.0 * np.sin(X_test.ravel()) +0.2 * X_test.ravel()**2 + np.random.randn(10) * 0.5 )
y_test = y_test.astype(np.float32)


y_pred = model.predict(X_test)


def calculate_mse(predictions, targets):
    squared_errors = [(pred - target) ** 2 for pred, target in zip(predictions, targets)]
    return sum(squared_errors) / len(predictions)


mse = calculate_mse(y_pred, y_test)
print("Test MSE:", mse)




