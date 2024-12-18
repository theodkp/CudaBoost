import gbm_pybind

data = gbm_pybind.load_csv("data\iris.csv")

print(data.featureNames)