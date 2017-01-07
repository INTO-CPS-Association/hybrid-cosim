'''
Created on Mar 5, 2016

@author: claudio gomes
'''

class Utils(object):
    
    @staticmethod
    def copyMapToStateTrace(target, step, iteration, source):
        for var in source:
            Utils.copyValueToStateTrace(target, var, step, iteration, source)
    
    @staticmethod
    def getValuesUpToDate(source, vars_to_select, step, iteration):
        result = {}
        for var in vars_to_select:
            # Only up-to-date values go in the calculations.
            # If a calcfunction crash, it's because this FMU is not being used correctly
            if step < len(source[var]):
                if iteration < source[var][step]:
                    result[var] = source[var][step][iteration]
        return result
    
    @staticmethod
    def copyValueToStateTrace(target, var, step, iteration, source):
        assert target.has_key(var)
        if step == len(target[var]):
            target[var].append([source[var]])
        elif iteration == len(target[var][step]):
            target[var][step].append(source[var])
        else:
            target[var][step][iteration] = source[var]
    
    @staticmethod
    def trimList(listToTrim, target_size):
        assert target_size <= len(listToTrim)
        assert target_size >= 0
        while target_size < len(listToTrim):
            del listToTrim[-1]
        assert target_size == len(listToTrim)