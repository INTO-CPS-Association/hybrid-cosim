'''
Created on Mar 5, 2016

@author: claudio gomes
'''

class Utils(object):
    
    @staticmethod
    def copyMapToStateTrace(target, step, iteration, source, ensureExists):
        for var in source:
            Utils.copyValueToStateTrace(target, var, step, iteration, source[var], ensureExists)
    
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
    def copyValueToStateTrace(target, var, step, iteration, value, ensureExists):
        if ensureExists:
            assert target.has_key(var)
        elif not target.has_key(var):
            return
        
        assert step <= len(target[var])
        if step == len(target[var]):
            target[var].append([value])
        elif step < len(target[var]):
            assert step == len(target[var]) - 1, "Makes no sense to rewrite past steps, without rolling back first. len(target[var])={}".format(len(target[var]))
            if iteration == len(target[var][step]):
                target[var][step].append(value)
            elif iteration < len(target[var][step]):
                assert iteration == len(target[var][step]) - 1, "Weird use of the iteration records. Either rewrite the last iteration, or never rewrite them (in case you want to keep track of them."
                target[var][step][iteration] = value
        """
        elif iteration == len(target[var][step]):
            target[var][step].append(value)
        else:
            target[var][step][iteration] = value
        """
    
    @staticmethod
    def trimList(listToTrim, target_size):
        assert target_size >= 0
        if target_size > len(listToTrim):
            return
        
        while target_size < len(listToTrim):
            del listToTrim[-1]
        assert target_size == len(listToTrim)